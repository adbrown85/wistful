/*
 * GglWindowGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowGlx.hpp"
PFNGLXCCAA GglWindowGlx::glXCreateContextAttribsARB = getGlXCCAA();

/** Creates a window for GLX. */
GglWindowGlx::GglWindowGlx() {
    this->display = NULL;
    this->info = NULL;
    this->window = NULL;
    this->context = NULL;
}

/** Destroys the window. */
GglWindowGlx::~GglWindowGlx() {
    ;
}

/** Shows the window. */
void GglWindowGlx::doOpen() {
    
    GglConfigGlx *config = createConfig();
    
    display = getDefaultDisplay();
    info = glXGetVisualFromFBConfig(display, config->getFBConfig());
    
    createXWindow();
    mapXWindow();
    
    context = createContext(display, config->getFBConfig());
    if (context == NULL) {
        XDestroyWindow(display, window);
        window = NULL;
        XCloseDisplay(display);
        display = NULL;
        throw GglException("Could not create context!");
    }
    glXMakeCurrent(display, window, context);
    
    glViewport(0, 0, 512, 512);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glXSwapBuffers(display, window);
}

/**
 * Closes the window.
 */
void GglWindowGlx::doClose() {
    glXDestroyContext(display, context);
    context = NULL;
    XDestroyWindow(display, window);
    window = NULL;
    XCloseDisplay(display);
    display = NULL;
}

/**
 * Returns next event from window.
 */
GglEvent GglWindowGlx::doGetEvent() {
	
	XEvent xEvent;
	
    XSelectInput(display, window, ExposureMask);
	XNextEvent(display, &xEvent);
	switch (xEvent.type) {
	case ClientMessage:
		return GglEvent(DESTROY);
	default:
		return GglEvent(OTHER);
	}
}

//---------------------------------------------------------
// Helpers
//

/**
 * Returns an OpenGL configuration for use with the window. 
 */
GglConfigGlx* GglWindowGlx::createConfig() {
    
    GglConfigFactory cf;
    map<int,int> reqs;
    
    reqs[GLX_X_RENDERABLE] = 1;
    reqs[GLX_DRAWABLE_TYPE] = GLX_WINDOW_BIT;
    reqs[GLX_RENDER_TYPE] = GLX_RGBA_BIT;
    reqs[GLX_CONFIG_CAVEAT] = GLX_NONE;
    reqs[GLX_DOUBLEBUFFER] = 1;
    reqs[GLX_RED_SIZE] = 8;
    reqs[GLX_GREEN_SIZE] = 8;
    reqs[GLX_BLUE_SIZE] = 8;
    reqs[GLX_ALPHA_SIZE] = 8;
    
    return (GglConfigGlx*) cf.create(reqs);
}

/**
 * Creates a context for the window.
 * 
 * @param display Machine window will appear on
 * @param config Framebuffer configuration
 * @return OpenGL context
 * @throw GglException if could not create context
 */
GLXContext GglWindowGlx::createContext(Display *display,
                                       GLXFBConfig config) {
    
    XErrorHandler handler = NULL;
    GLXContext context = NULL;
    GLint attribs[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 2,
            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            NULL
    };
    
    handler = XSetErrorHandler(&x11ErrorHandler);
    context = glXCreateContextAttribsARB(
            display,  // display
            config,   // framebuffer configuration
            0,        // render type
            True,     // direct
            attribs); // attributes
    XSetErrorHandler(handler);
    
    if (context == NULL) {
        throw GglException("Could not create OpenGL 3.2 context!");
    }
    return context;
}

/**
 * Returns a pointer to the default display.
 * 
 * @throw GglException if could not open display
 * @return Pointer to the display
 */
Display* GglWindowGlx::getDefaultDisplay() {
    
    Display *display = XOpenDisplay(NULL);
    
    if (display == NULL) {
        throw GglException("Could not open default display!");
    }
    return display;
}

/**
 * Returns an event mask for use with the window.
 */
long GglWindowGlx::getEventMask() {
    return ExposureMask
            | StructureNotifyMask
            | VisibilityChangeMask
            | KeyPressMask
            | PointerMotionMask;
}

/**
 * Returns a color map for the window.
 */
Colormap GglWindowGlx::getColormap() {
    return XCreateColormap(
            display,
            RootWindow(display, info->screen),
            info->visual,
            AllocNone);
}

/**
 * Returns mask for specifying window properties.
 */
long GglWindowGlx::getWindowMask() {
	return CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;
}

/**
 * Return window attributes needed to create backing X window.
 */
XSetWindowAttributes GglWindowGlx::getWindowAttributes() {
    
    XSetWindowAttributes wa;
    
    wa.event_mask = getEventMask();
    wa.border_pixel = 0;
    wa.bit_gravity = StaticGravity;
    wa.colormap = getColormap();
    return wa;
}

/**
 * Makes an X window to back the GGL window.
 */
void GglWindowGlx::createXWindow() {
    
    int winmask = getWindowMask();
    XSetWindowAttributes wa = getWindowAttributes();
    Atom atom = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    
    window = XCreateWindow(
            display,
            DefaultRootWindow(display),
            0, 0,
            512, 512,
            0,
            info->depth,
            InputOutput,
            info->visual,
            winmask,
            &wa);
    XSetWMProtocols(display, window, &atom, 1);
}

/**
 * Shows the X window on a screen.
 */
void GglWindowGlx::mapXWindow() {
    
    XEvent event;
    
    XMapWindow(display, window);
    XSelectInput(display, window, StructureNotifyMask);
    XNextEvent(display, &event);
    while (event.type != MapNotify) {
        XNextEvent(display, &event);
    }
}

/**
 * Returns pointer to <i>glXCreateContextAttribsARB</i> function.
 */
PFNGLXCCAA GglWindowGlx::getGlXCCAA() {
    
    GLubyte *name = (GLubyte*) "glXCreateContextAttribsARB";
    
    return (PFNGLXCCAA) glXGetProcAddressARB(name);
}

/**
 * Handles error events from X11.
 * 
 * @param display Machine displaying content
 * @param event X11 error event
 * @return Arbitrary integer, which is ignored
 */
int GglWindowGlx::x11ErrorHandler(Display *display, XErrorEvent *event) {
    return 0;
}

