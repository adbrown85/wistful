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
	GglWindow();
	virtual ~GglWindow();
	virtual void show() = 0;
};

#endif
