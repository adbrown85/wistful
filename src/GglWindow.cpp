/*
 * GglWindow.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindow.hpp"

/** Creates a window for GLX. */
GglWindowGlx::GglWindowGlx() {
	display = XOpenDisplay(getenv("DISPLAY"));
}

/** Destroys the window. */
GglWindowGlx::~GglWindowGlx() {
	XCloseDisplay(display);
}

/** Shows the window. */
void GglWindowGlx::show() {
	cout << "GlWindowGlx::show()" << endl;
}

