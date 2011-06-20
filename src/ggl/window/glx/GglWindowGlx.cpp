/*
 * GglWindowGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/glx/GglWindowGlx.hpp"
PFNGLXCCAA GglWindowGlx::glXCreateContextAttribsARB = getGlXCCAA();
long GglWindowGlx::DEFAULT_EVENT_MASK = getEventMask();

/**
 * Creates a GLX window from a window format.
 * 
 * @param wf Container with window settings
 */
GglWindowGlx::GglWindowGlx(const Ggl::WindowFormat &wf) : Ggl::Window(wf) {
    this->closed = false;
    this->display = NULL;
    this->info = NULL;
    this->window = 0;
    this->context = NULL;
    this->config = createConfig(wf);
}

/**
 * Destroys the window.
 */
GglWindowGlx::~GglWindowGlx() {
    ;
}

void GglWindowGlx::doCreateConnection() throw(std::exception) {
    
    display = XOpenDisplay(NULL);
    
    if (display == NULL) {
        throw GglException("Could not open default display!");
    }
}

void GglWindowGlx::doDestroyConnection() {
    XCloseDisplay(display);
    display = NULL;
}

void GglWindowGlx::doCreateWindow() throw(std::exception) {
    
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
}

/**
 * Makes the window visible.
 */
void GglWindowGlx::doActivateWindow() {
    XMapWindow(display, window);
    XFlush(display);
}

void GglWindowGlx::doDestroyWindow() {
    XDestroyWindow(display, window);
    window = 0;
}

void GglWindowGlx::doCreateContext() throw(std::exception) {
    
    XErrorHandler handler = NULL;
    GLint attribs[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 2,
            GLX_CONTEXT_MINOR_VERSION_ARB, 1,
//            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            (GLint) NULL
    };
    
    // Remove default error handler
    handler = XSetErrorHandler(&x11ErrorHandler);
    
    // Create context
    context = glXCreateContextAttribsARB(
            display,  // display
            config,   // framebuffer configuration
            0,        // render type
            True,     // direct
            attribs); // attributes
    
    // Restore default error handler
    XSetErrorHandler(handler);
    
    // Check if not made correctly
    if (context == NULL) {
        throw GglException("Could not make OpenGL context!");
    }
}

/**
 * Makes the OpenGL context current.
 */
void GglWindowGlx::doActivateContext() {
    glXMakeCurrent(display, window, context);
}

void GglWindowGlx::doDestroyContext() {
    glXDestroyContext(display, context);
    context = NULL;
}

void GglWindowGlx::doFlush() {
    glXSwapBuffers(display, window);
}

/**
 * Starts the run loop.
 */
void GglWindowGlx::doRun() {
    while (!closed) {
        Ggl::WindowEvent event = getEvent();
        switch (event.getType()) {
        case Ggl::MAP:
            fireInitEvent();
            break;
        case Ggl::EXPOSE:
            fireDisplayEvent();
            break;
        case Ggl::DESTROY:
            fireDestroyEvent();
            close();
            break;
        case Ggl::KEY:
            fireKeyEvent(event.getTrigger());
            break;
        default:
            continue;
        }
    }
}

void GglWindowGlx::doClose() {
    closed = true;
}

//---------------------------------------------------------
// Helpers
//

/**
 * Creates visual information about a screen.
 * 
 * @param display Connection to machine showing content
 * @param fbc Desired framebuffer configuration of window
 * @return Visual information about a compatible window
 */
XVisualInfo* GglWindowGlx::createInfo(Display *display,
                                      const GLXFBConfig &fbc) {
    return glXGetVisualFromFBConfig(display, fbc);
}

/**
 * Returns an OpenGL configuration for use with the window. 
 */
GLXFBConfig GglWindowGlx::createConfig() {
    
    GglConfigFactoryGlx cf;
    std::map<int,int> reqs;
    
    reqs[GLX_X_RENDERABLE] = 1;
    reqs[GLX_DRAWABLE_TYPE] = GLX_WINDOW_BIT;
    reqs[GLX_RENDER_TYPE] = GLX_RGBA_BIT;
    reqs[GLX_CONFIG_CAVEAT] = GLX_NONE;
    reqs[GLX_DOUBLEBUFFER] = 1;
    reqs[GLX_RED_SIZE] = 8;
    reqs[GLX_GREEN_SIZE] = 8;
    reqs[GLX_BLUE_SIZE] = 8;
    reqs[GLX_ALPHA_SIZE] = 8;
    
    return cf.create(reqs);
}

/**
 * Returns an OpenGL configuration for use with the window.
 * 
 * @param wf Container with window settings
 */
GLXFBConfig GglWindowGlx::createConfig(const Ggl::WindowFormat &wf) {
    
    GglConfigFactoryGlx cf;
    
    return cf.create(wf);
}

/**
 * Returns next event from window.
 */
Ggl::WindowEvent GglWindowGlx::getEvent() {
    
    XEvent xEvent;
    
    XSelectInput(display, window, DEFAULT_EVENT_MASK);
    
    while (true) {
        XNextEvent(display, &xEvent);
        switch (xEvent.type) {
        case ClientMessage:
            return Ggl::WindowEvent(Ggl::DESTROY);
        case MapNotify:
            return Ggl::WindowEvent(Ggl::MAP);
        case Expose:
            if (xEvent.xexpose.count == 0) {
                return Ggl::WindowEvent(Ggl::EXPOSE);
            }
        case KeyPress:
            return toGglEvent(xEvent.xkey);
        default:
            return Ggl::WindowEvent(Ggl::OTHER);
        }
    }
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
void GglWindowGlx::subscribe(Display *display, int window) {
    
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
Ggl::WindowEvent GglWindowGlx::toGglEvent(XKeyEvent &xke) {
    
    Ggl::WindowEvent ge(Ggl::KEY);
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
