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
	GglWindowGlx(GglConfigGlx *cfg);
	virtual ~GglWindowGlx();
	virtual void show();
private:
	Display *display;
	Window window;
	XVisualInfo *visual;
// Helpers
	static Display* getDefaultDisplay();
	static long getEventMask();
	static Colormap getColormap(Display *display, XVisualInfo *vi);
};

#endif
