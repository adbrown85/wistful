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
// Helpers
	static Display* getDefaultDisplay();
};

#endif
