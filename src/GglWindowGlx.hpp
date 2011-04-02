/*
 * GglWindowGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWGLX_HPP
#define GGLWINDOWGLX_HPP
#include "common.h"
#include "GglWindow.hpp"
#include "GglException.hpp"
#include "GglConfigFactory.hpp"
typedef PFNGLXCREATECONTEXTATTRIBSARBPROC PFNGLXCCAA;


/** @brief OpenGL Window implemented with GLX. */
class GglWindowGlx : public GglWindow {
public:
    GglWindowGlx();
    virtual ~GglWindowGlx();
protected:
    virtual bool doCreateConnection();
    virtual bool doCreateWindow();
    virtual bool doCreateContext();
    virtual void doDestroyConnection();
    virtual void doDestroyWindow();
    virtual void doDestroyContext();
    virtual void doFlush();
    virtual GglEvent doGetEvent();
private:
    Display *display;
    XVisualInfo *info;
    Window window;
    GLXContext context;
    GglConfigGlx *config;
// Helpers
    static GglConfigGlx* createConfig();
    static Display* getDefaultDisplay();
    static long getEventMask();
    static long getWindowMask();
    Colormap getColormap();
    XSetWindowAttributes getWindowAttributes();
    static GLXContext createContext(Display *d, Window w, GLXFBConfig c);
    void createXWindow();
    void mapXWindow();
    static int x11ErrorHandler(Display *display, XErrorEvent *event);
// Function pointers
    static PFNGLXCCAA getGlXCCAA();
    static PFNGLXCCAA glXCreateContextAttribsARB;
};

#endif
