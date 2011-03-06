/*
 * GlWindow.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLWINDOW_HPP
#define GLWINDOW_HPP
#include "common.h"


/** @brief OpenGL window that can be shown. */
class GlWindow {
public:
	GlWindow();
	virtual ~GlWindow();
	virtual void show() = 0;
};

#endif
