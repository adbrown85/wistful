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


/** @brief OpenGL Window implemented with GLX. */
class GglWindowGlx {
public:
	GglWindowGlx(GglConfigGlx *config);
	virtual ~GglWindowGlx();
	virtual void open();
	virtual void close();
private:
	GglConfigGlx *config;
	Display *display;
	XVisualInfo *info;
	Window window;
// Helpers
	static Display* getDefaultDisplay();
	static long getEventMask();
	static long getWindowMask();
	Colormap getColormap();
	XSetWindowAttributes getWindowAttributes();
	void createXWindow();
	void mapXWindow();
};

#endif
