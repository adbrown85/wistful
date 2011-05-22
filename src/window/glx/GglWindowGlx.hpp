/*
 * GglWindowGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWGLX_HPP
#define GGLWINDOWGLX_HPP
#include "ggl_common.h"
#include "GglWindow.hpp"
#include "GglException.hpp"
#include "GglConfigFactoryGlx.hpp"

typedef PFNGLXCREATECONTEXTATTRIBSARBPROC PFNGLXCCAA;


/**
 * @brief OpenGL Window implemented with GLX.
 */
class GglWindowGlx : public GglWindow {
public:
    GglWindowGlx();
    virtual ~GglWindowGlx();
protected:
    virtual void doActivateContext();
    virtual void doActivateWindow();
    virtual void doCreateConnection() throw(GglException);
    virtual void doCreateWindow() throw(GglException);
    virtual void doCreateContext() throw(GglException);
    virtual void doDestroyConnection();
    virtual void doDestroyWindow();
    virtual void doDestroyContext();
    virtual void doFlush();
    virtual void doRun();
    virtual GglEvent doGetEvent();
private:
    Display *display;
    XVisualInfo *info;
    Window window;
    GLXContext context;
    GglConfigGlx *config;
// Helpers
    static void subscribe(Display *display, Window window);
    static GglConfigGlx* createConfig();
    static XVisualInfo* createInfo(Display *display, GglConfigGlx *config);
    static long getEventMask();
    static long getWindowMask();
    static Colormap getColormap(Display *display, XVisualInfo *vi);
    static XSetWindowAttributes getWindowAttributes(Colormap cm);
    static GglEvent toGglEvent(XKeyEvent &xke);
    static int x11ErrorHandler(Display *display, XErrorEvent *event);
// Function pointers
    static PFNGLXCCAA getGlXCCAA();
    static PFNGLXCCAA glXCreateContextAttribsARB;
// Constants
    static long DEFAULT_EVENT_MASK;
};

#endif
