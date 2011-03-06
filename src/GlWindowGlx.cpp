/*
 * GlWindowGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GlWindowGlx.hpp"

/** Creates a window. */
GlWindowGlx::GlWindowGlx() {
	display = XOpenDisplay(getenv("DISPLAY"));
}

/** Destroys the window. */
GlWindowGlx::~GlWindowGlx() {
	XCloseDisplay(display);
}

/** Shows the window. */
void GlWindowGlx::show() {
	cout << "GlWindowGlx::show()" << endl;
}
