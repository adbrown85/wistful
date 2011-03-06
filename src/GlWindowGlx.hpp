/*
 * GlWindowGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLWINDOWGLX_HPP
#define GLWINDOWGLX_HPP
#include "common.h"
#include "GlWindow.hpp"


/** OpenGL Window implemented with GLX. */
class GlWindowGlx {
public:
	GlWindowGlx();
	virtual ~GlWindowGlx();
	virtual void show();
private:
	Display *display;
};

#endif
