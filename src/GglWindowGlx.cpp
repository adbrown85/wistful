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
    this->config = NULL;
}

/** Destroys the window. */
GglWindowGlx::~GglWindowGlx() {
    ;
}

bool GglWindowGlx::doCreateConnection() {
	display = getDefaultDisplay();
	return (display != NULL);
}

void GglWindowGlx::doDestroyConnection() {
    XCloseDisplay(display);
    display = NULL;
}

bool GglWindowGlx::doCreateWindow() {
	
    config = createConfig();
    info = createInfo(display, config);
    createXWindow();
    mapXWindow();
    
    return true;
}

void GglWindowGlx::doDestroyWindow() {
    XDestroyWindow(display, window);
    window = NULL;
}

bool GglWindowGlx::doCreateContext() {
    
    XErrorHandler handler = NULL;
    GLXContext context = NULL;
    GLXFBConfig fbc = config->getFBConfig();
    GLint attribs[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 2,
            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            NULL
    };
    
    // Remove default error handler
    handler = XSetErrorHandler(&x11ErrorHandler);
    
    // Create context
    context = glXCreateContextAttribsARB(
            display,  // display
            fbc,      // framebuffer configuration
            0,        // render type
            True,     // direct
            attribs); // attributes
    
    // Check if created correctly
    if (context == NULL) {
    	return false;
    }
    
    // Make it current
    glXMakeCurrent(display, window, context);
    
    // Restore default error handler
    XSetErrorHandler(handler);
    
    // Successfully made
    return true;
}

void GglWindowGlx::doDestroyContext() {
    glXDestroyContext(display, context);
    context = NULL;
}

void GglWindowGlx::doFlush() {
    glXSwapBuffers(display, window);
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
 * Creates visual information about a screen.
 * 
 * @param display Connection to machine showing content
 * @param config Desired framebuffer configuration of window
 * @return Visual information about a compatible window
 */
XVisualInfo* GglWindowGlx::createInfo(Display *display, GglConfigGlx *config) {
    return glXGetVisualFromFBConfig(display, config->getFBConfig());
}

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
 * 
 * @param display Connection to machine showing content
 * @param vi Visual information about X screen
 */
Colormap GglWindowGlx::getColormap(Display *display, XVisualInfo *vi) {
    return XCreateColormap(
            display,
            RootWindow(display, vi->screen),
            vi->visual,
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
 * 
 * @param cm Description of color capabilities of screen
 */
XSetWindowAttributes GglWindowGlx::getWindowAttributes(Colormap cm) {
    
    XSetWindowAttributes wa;
    
    wa.event_mask = getEventMask();
    wa.border_pixel = 0;
    wa.bit_gravity = StaticGravity;
    wa.colormap = cm;
    return wa;
}

/**
 * Makes an X window to back the GGL window.
 */
void GglWindowGlx::createXWindow() {
    
    int winmask = getWindowMask();
    Colormap cm = getColormap(display, info);
    XSetWindowAttributes wa = getWindowAttributes(cm);
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

