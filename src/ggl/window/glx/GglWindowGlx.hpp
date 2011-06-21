/*
 * GglWindowGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_WINDOWGLX_HPP
#define GGL_WINDOWGLX_HPP
#include "ggl/common.h"
#include "ggl/GglException.hpp"
#include "ggl/window/GglWindow.hpp"
#include "ggl/window/glx/GglConfigFactoryGlx.hpp"
namespace Ggl {

typedef PFNGLXCREATECONTEXTATTRIBSARBPROC PFNGLXCCAA;


/**
 * @brief OpenGL Window implemented with GLX.
 */
class WindowGlx : public Window {
public:
    WindowGlx(const WindowFormat &wf);
    virtual ~WindowGlx();
protected:
    virtual void doActivateContext();
    virtual void doActivateWindow();
    virtual void doClose();
    virtual void doCreateConnection() throw(std::exception);
    virtual void doCreateWindow() throw(std::exception);
    virtual void doCreateContext() throw(std::exception);
    virtual void doDestroyConnection();
    virtual void doDestroyWindow();
    virtual void doDestroyContext();
    virtual void doFlush();
    virtual void doRun();
private:
    bool closed;
    Display *display;
    XVisualInfo *info;
    int window;
    GLXContext context;
    GLXFBConfig config;
// Helpers
    WindowEvent getEvent();
    static void subscribe(Display *display, int window);
    static GLXFBConfig createConfig();
    static GLXFBConfig createConfig(const WindowFormat &wf);
    static XVisualInfo* createInfo(Display *display, const GLXFBConfig &fbc);
    static long getEventMask();
    static long getWindowMask();
    static Colormap getColormap(Display *display, XVisualInfo *vi);
    static XSetWindowAttributes getWindowAttributes(Colormap cm);
    static WindowEvent toGglEvent(XKeyEvent &xke);
    static int x11ErrorHandler(Display *display, XErrorEvent *event);
// Function pointers
    static PFNGLXCCAA getGlXCCAA();
    static PFNGLXCCAA glXCreateContextAttribsARB;
// Constants
    static long DEFAULT_EVENT_MASK;
};

}
#endif
