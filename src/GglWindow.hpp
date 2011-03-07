/*
 * GglWindow.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOW_HPP
#define GGLWINDOW_HPP
#include "common.h"


/** @brief OpenGL window that can be shown. */
class GglWindow {
public:
	GglWindow();
	virtual ~GglWindow();
	virtual void show() = 0;
};


/** @brief OpenGL Window implemented with GLX. */
class GglWindowGlx {
public:
	GglWindowGlx();
	virtual ~GglWindowGlx();
	virtual void show();
private:
	Display *display;
};

#endif
