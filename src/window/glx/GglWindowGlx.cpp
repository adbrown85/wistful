/*
 * GglWindowGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowGlx.hpp"
#ifdef HAVE_GLX
PFNGLXCCAA GglWindowGlx::glXCreateContextAttribsARB = getGlXCCAA();
long GglWindowGlx::DEFAULT_EVENT_MASK = getEventMask();
#endif //HAVE_GLX

/** Creates a window for GLX. */
GglWindowGlx::GglWindowGlx() {
#ifdef HAVE_GLX
    this->display = NULL;
    this->info = NULL;
    this->window = NULL;
    this->context = NULL;
    this->config = createConfig();
#endif
}

/** Destroys the window. */
GglWindowGlx::~GglWindowGlx() {
    ;
}


void GglWindowGlx::doCreateConnection() throw(GglException) {
#ifdef HAVE_GLX
    display = XOpenDisplay(NULL);
    
    if (display == NULL) {
        throw GglException("Could not open default display!");
    }
#endif
}

void GglWindowGlx::doDestroyConnection() {
#ifdef HAVE_GLX
    XCloseDisplay(display);
    display = NULL;
#endif
}

void GglWindowGlx::doCreateWindow() throw(GglException) {
#ifdef HAVE_GLX
    int winmask = getWindowMask();
    XVisualInfo *info = createInfo(display, config);
    Colormap cm = getColormap(display, info);
    XSetWindowAttributes wa = getWindowAttributes(cm);
    
    window = XCreateWindow(
            display,
            DefaultRootWindow(display),
            getX(), getY(),
            getWidth(), getHeight(),
            0,
            info->depth,
            InputOutput,
            info->visual,
            winmask,
            &wa);
    
    subscribe(display, window);
#endif
}

/**
 * Makes the window visible.
 */
void GglWindowGlx::doActivateWindow() {
#ifdef HAVE_GLX
    XMapWindow(display, window);
    XFlush(display);
#endif
}

void GglWindowGlx::doDestroyWindow() {
#ifdef HAVE_GLX
    XDestroyWindow(display, window);
    window = NULL;
#endif
}

void GglWindowGlx::doCreateContext() throw(GglException) {
#ifdef HAVE_GLX
    XErrorHandler handler = NULL;
    GLXFBConfig fbc = config->getFBConfig();
    GLint attribs[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 2,
            GLX_CONTEXT_MINOR_VERSION_ARB, 1,
//            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
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
    
    // Restore default error handler
    XSetErrorHandler(handler);
    
    // Check if not made correctly
    if (context == NULL) {
        throw GglException("Could not make OpenGL context!");
    }
#endif
}

/**
 * Makes the OpenGL context current.
 */
void GglWindowGlx::doActivateContext() {
#ifdef HAVE_GLX
    glXMakeCurrent(display, window, context);
#endif
}

void GglWindowGlx::doDestroyContext() {
#ifdef HAVE_GLX
    glXDestroyContext(display, context);
    context = NULL;
#endif
}

void GglWindowGlx::doFlush() {
#ifdef HAVE_GLX
    glXSwapBuffers(display, window);
#endif
}

/**
 * Returns next event from window.
 */
GglEvent GglWindowGlx::doGetEvent() {
#ifdef HAVE_GLX
    XEvent xEvent;
    
    XSelectInput(display, window, DEFAULT_EVENT_MASK);
    
    while (true) {
        XNextEvent(display, &xEvent);
        switch (xEvent.type) {
        case ClientMessage:
            return GglEvent(DESTROY);
        case MapNotify:
            return GglEvent(MAP);
        case Expose:
            if (xEvent.xexpose.count == 0) {
                return GglEvent(EXPOSE);
            }
        case KeyPress:
            return toGglEvent(xEvent.xkey);
        default:
            return GglEvent(OTHER);
        }
    }
#else
    return GglEvent(DESTROY);
#endif
}

#ifdef HAVE_GLX

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
    
    GglConfigFactoryGlx cf;
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
 * Subscribes to window manager events.
 * 
 * @param display Connection to machine showing content
 * @param window Handle to X11 window
 */
void GglWindowGlx::subscribe(Display *display, Window window) {
    
    Atom atom = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    
    XSetWMProtocols(display, window, &atom, 1);
}

/**
 * Returns pointer to <i>glXCreateContextAttribsARB</i> function.
 */
PFNGLXCCAA GglWindowGlx::getGlXCCAA() {
    
    GLubyte *name = (GLubyte*) "glXCreateContextAttribsARB";
    
    return (PFNGLXCCAA) glXGetProcAddressARB(name);
}

/**
 * Converts an X11 key event to a GGL event.
 * 
 * @param xke X11 Key event
 * @return Equivalent GGL event
 */
GglEvent GglWindowGlx::toGglEvent(XKeyEvent &xke) {
    
    GglEvent ge(KEY);
    KeySym ks = XLookupKeysym(&xke, 0);
    
    ge.setTrigger(ks);
    return ge;
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

#endif //HAVE_GLX
