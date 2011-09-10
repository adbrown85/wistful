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
    
    XEvent event;
    
    XSelectInput(display, window, DEFAULT_EVENT_MASK);
    
    while (!closed) {
        XNextEvent(display, &event);
        switch (event.type) {
        case ClientMessage:
            fireDestroyEvent();
            break;
        case MapNotify:
            fireInitEvent();
            break;
        case Expose:
            if (event.xexpose.count == 0) {
                fireDisplayEvent();
            }
            break;
        case KeyPress:
            fireKeyEvent(XLookupKeysym(&(event.xkey), 0));
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
 * Handles error events from X11.
 * 
 * @param display Machine displaying content
 * @param event X11 error event
 * @return Arbitrary integer, which is ignored
 */
int WindowGlx::x11ErrorHandler(Display *display, XErrorEvent *event) {
    return 0;
}

// NESTED CLASSES

/**
 * Creates an OpenGL configuration factory.
 */
WindowGlx::ConfigFactoryGlx::ConfigFactoryGlx() {
    display = createDisplay();
}

/**
 * Destroys the factory.
 */
WindowGlx::ConfigFactoryGlx::~ConfigFactoryGlx() {
    XCloseDisplay(display);
}

/**
 * Returns OpenGL configuration matching a window format.
 * 
 * @param wf Container with window settings
 */
GLXFBConfig WindowGlx::ConfigFactoryGlx::create(const WindowFormat &wf) {
    
    map<int,int> m;
    int colorComponentSize = wf.getColorSize() / 8;
    
    m[GLX_X_RENDERABLE] = 1;
    m[GLX_DRAWABLE_TYPE] = GLX_WINDOW_BIT;
    m[GLX_RENDER_TYPE] = GLX_RGBA_BIT;
    m[GLX_CONFIG_CAVEAT] = GLX_NONE;
    m[GLX_DOUBLEBUFFER] = 1;
    m[GLX_RED_SIZE] = colorComponentSize;
    m[GLX_GREEN_SIZE] = colorComponentSize;
    m[GLX_BLUE_SIZE] = colorComponentSize;
    m[GLX_ALPHA_SIZE] = wf.getAlphaSize();
    m[GLX_DEPTH_SIZE] = wf.getDepthSize();
    
    return create(m);
}

/**
 * Returns OpenGL configurations meeting certain requirements.
 */
GLXFBConfig
WindowGlx::ConfigFactoryGlx::create(const map<int,int> &requirements) {
    
    const int *reqs = toArray(requirements);
    int len;
    GLXFBConfig *fbcs = glXChooseFBConfig(display, 0, reqs, &len);
    GLXFBConfig config;
    
    // Validate
    if (len == 0) {
        throw Exception("No configuration found for requirements!");
    }
    
    // Copy the first config
    config = fbcs[0];
    
    // Clean up
    delete[] reqs;
    XFree(fbcs);
    
    return config;
}

/**
 * Returns pointer to the default X display.
 */
Display* WindowGlx::ConfigFactoryGlx::createDisplay() {
    return XOpenDisplay(NULL);
}

/**
 * Converts a map of integers to an array.
 * 
 * @param m Map of integers to integers
 * @return Pointer to NULL-terminated array
 */
const int* WindowGlx::ConfigFactoryGlx::toArray(const map<int,int> &m) {
    
    int len = (m.size() * 2) + 1;           // Length of array
    int *arr = new int[len];                // Array of integers
    map<int,int>::const_iterator it;        // Iterator over map
    int i = 0;                              // Index into array
    
    for (it=m.begin(); it!=m.end(); ++it) {
        arr[i++] = it->first;
        arr[i++] = it->second;
    }
    arr[i] = (int) NULL;
    return const_cast<const int*>(arr);
}

