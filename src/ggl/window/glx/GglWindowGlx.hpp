/*
 * GglWindowGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWGLX_HPP
#define GGLWINDOWGLX_HPP
#include "ggl/common.h"
#include "ggl/GglException.hpp"
#include "ggl/window/GglWindow.hpp"
#include "ggl/window/glx/GglConfigFactoryGlx.hpp"

typedef PFNGLXCREATECONTEXTATTRIBSARBPROC PFNGLXCCAA;


/**
 * @brief OpenGL Window implemented with GLX.
 */
class GglWindowGlx : public GglWindow {
public:
    GglWindowGlx(const GglWindowFormat &wf);
    virtual ~GglWindowGlx();
protected:
    virtual void doActivateContext();
    virtual void doActivateWindow();
    virtual void doCreateConnection() throw(std::exception);
    virtual void doCreateWindow() throw(std::exception);
    virtual void doCreateContext() throw(std::exception);
    virtual void doDestroyConnection();
    virtual void doDestroyWindow();
    virtual void doDestroyContext();
    virtual void doFlush();
    virtual void doRun();
private:
    Display *display;
    XVisualInfo *info;
    Window window;
    GLXContext context;
    GLXFBConfig config;
// Helpers
    GglWindowEvent getEvent();
    static void subscribe(Display *display, Window window);
    static GLXFBConfig createConfig();
    static GLXFBConfig createConfig(const GglWindowFormat &wf);
    static XVisualInfo* createInfo(Display *display, const GLXFBConfig &fbc);
    static long getEventMask();
    static long getWindowMask();
    static Colormap getColormap(Display *display, XVisualInfo *vi);
    static XSetWindowAttributes getWindowAttributes(Colormap cm);
    static GglWindowEvent toGglEvent(XKeyEvent &xke);
    static int x11ErrorHandler(Display *display, XErrorEvent *event);
// Function pointers
    static PFNGLXCCAA getGlXCCAA();
    static PFNGLXCCAA glXCreateContextAttribsARB;
// Constants
    static long DEFAULT_EVENT_MASK;
};

#endif
