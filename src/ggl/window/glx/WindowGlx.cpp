/*
 * WindowGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/glx/WindowGlx.hpp"
using namespace Ggl;
using namespace std;

PFNGLXCCAA WindowGlx::glXCreateContextAttribsARB = getGlXCCAA();
long WindowGlx::DEFAULT_EVENT_MASK = getEventMask();

/**
 * Creates a GLX window from a window format.
 * 
 * @param wf Container with window settings
 */
WindowGlx::WindowGlx(const WindowFormat &wf) : Window(wf) {
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
WindowGlx::~WindowGlx() {
    ;
}

void WindowGlx::doCreateConnection() throw(exception) {
    
    display = XOpenDisplay(NULL);
    
    if (display == NULL) {
        throw Exception("Could not open default display!");
    }
}

void WindowGlx::doDestroyConnection() {
    XCloseDisplay(display);
    display = NULL;
}

void WindowGlx::doCreateWindow() throw(exception) {
    
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
void WindowGlx::doActivateWindow() {
    XMapWindow(display, window);
    XFlush(display);
}

void WindowGlx::doDestroyWindow() {
    XDestroyWindow(display, window);
    window = 0;
}

void WindowGlx::doCreateContext() throw(exception) {
    
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
        throw Exception("Could not make OpenGL context!");
    }
}

/**
 * Makes the OpenGL context current.
 */
void WindowGlx::doActivateContext() {
    glXMakeCurrent(display, window, context);
}

void WindowGlx::doDestroyContext() {
    glXDestroyContext(display, context);
    context = NULL;
}

void WindowGlx::doFlush() {
    glXSwapBuffers(display, window);
}

/**
 * Starts the run loop.
 */
void WindowGlx::doRun() {
    while (!closed) {
        WindowEvent event = getEvent();
        switch (event.getType()) {
        case MAP:
            fireInitEvent();
            break;
        case EXPOSE:
            fireDisplayEvent();
            break;
        case DESTROY:
            fireDestroyEvent();
            close();
            break;
        case KEY:
            fireKeyEvent(event.getTrigger());
            break;
        default:
            continue;
        }
    }
}

void WindowGlx::doClose() {
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
XVisualInfo* WindowGlx::createInfo(Display *display,
                                   const GLXFBConfig &fbc) {
    return glXGetVisualFromFBConfig(display, fbc);
}

/**
 * Returns an OpenGL configuration for use with the window.
 * 
 * @param wf Container with window settings
 */
GLXFBConfig WindowGlx::createConfig(const WindowFormat &wf) {
    
    ConfigFactoryGlx cf;
    
    return cf.create(wf);
}

/**
 * Returns next event from window.
 */
WindowEvent WindowGlx::getEvent() {
    
    XEvent xEvent;
    
    XSelectInput(display, window, DEFAULT_EVENT_MASK);
    
    while (true) {
        XNextEvent(display, &xEvent);
        switch (xEvent.type) {
        case ClientMessage:
            return WindowEvent(DESTROY);
        case MapNotify:
            return WindowEvent(MAP);
        case Expose:
            if (xEvent.xexpose.count == 0) {
                return WindowEvent(EXPOSE);
            }
        case KeyPress:
            return toGglEvent(xEvent.xkey);
        default:
            return WindowEvent(OTHER);
        }
    }
}

/**
 * Returns an event mask for use with the window.
 */
long WindowGlx::getEventMask() {
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
Colormap WindowGlx::getColormap(Display *display, XVisualInfo *vi) {
    return XCreateColormap(
            display,
            RootWindow(display, vi->screen),
            vi->visual,
            AllocNone);
}

/**
 * Returns mask for specifying window properties.
 */
long WindowGlx::getWindowMask() {
    return CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;
}

/**
 * Return window attributes needed to create backing X window.
 * 
 * @param cm Description of color capabilities of screen
 */
XSetWindowAttributes WindowGlx::getWindowAttributes(Colormap cm) {
    
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
void WindowGlx::subscribe(Display *display, int window) {
    
    Atom atom = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    
    XSetWMProtocols(display, window, &atom, 1);
}

/**
 * Returns pointer to <i>glXCreateContextAttribsARB</i> function.
 */
PFNGLXCCAA WindowGlx::getGlXCCAA() {
    
    GLubyte *name = (GLubyte*) "glXCreateContextAttribsARB";
    
    return (PFNGLXCCAA) glXGetProcAddressARB(name);
}

/**
 * Converts an X11 key event to a GGL event.
 * 
 * @param xke X11 Key event
 * @return Equivalent GGL event
 */
WindowEvent WindowGlx::toGglEvent(XKeyEvent &xke) {
    
    WindowEvent ge(KEY);
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
int WindowGlx::x11ErrorHandler(Display *display, XErrorEvent *event) {
    return 0;
}
