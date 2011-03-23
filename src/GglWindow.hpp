/*
 * GglWindow.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOW_HPP
#define GGLWINDOW_HPP
#include "common.h"
#include "GglConfig.hpp"


/** @brief OpenGL window that can be shown. */
class GglWindow {
public:
	virtual ~GglWindow() {}
	virtual void show() = 0;
};


/** @brief OpenGL Window implemented with GLX. */
class GglWindowGlx {
public:
	GglWindowGlx(GglConfigGlx *cfg);
	virtual ~GglWindowGlx();
	virtual void show();
private:
	Display *display;
	Window window;
	XVisualInfo *visualInfo;
};

#endif
