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
typedef PFNGLXCREATECONTEXTATTRIBSARBPROC GLXCCAA;


/** @brief OpenGL Window implemented with GLX. */
class GglWindowGlx : public GglWindow {
public:
	GglWindowGlx();
	virtual ~GglWindowGlx();
	virtual void doOpen();
	virtual void doClose();
private:
	Display *display;
	XVisualInfo *info;
	Window window;
	GLXContext context;
// Helpers
	static GglConfigGlx* createConfig();
	static Display* getDefaultDisplay();
	static long getEventMask();
	static long getWindowMask();
	Colormap getColormap();
	XSetWindowAttributes getWindowAttributes();
	static GLXContext createContext(Display *display, GLXFBConfig config);
	void createXWindow();
	void mapXWindow();
// Function pointers
	static GLXCCAA getGlXCCAA();
	static GLXCCAA glXCreateContextAttribsARB;
};

#endif
