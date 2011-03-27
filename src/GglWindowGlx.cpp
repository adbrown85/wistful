/*
 * GglWindowGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowGlx.hpp"

/** Creates a window for GLX. */
GglWindowGlx::GglWindowGlx(GglConfigGlx *cfg) {
	display = getDefaultDisplay();
	visual = glXGetVisualFromFBConfig(display, cfg->getFBConfig());
}

/** Destroys the window. */
GglWindowGlx::~GglWindowGlx() {
	XDestroyWindow(display, window);
	XCloseDisplay(display);
}

/** Shows the window. */
void GglWindowGlx::show() {
	
	window = createXWindow();
	XMapWindow(display, window);
	
	GLXContext context = glXCreateContext(display, visual, 0, True);
	glXMakeCurrent(display, window, context);
	
	glViewport(0, 0, 512, 512);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glXSwapBuffers(display, window);
}

//---------------------------------------------------------
// Helpers
//

/**
 * Returns a pointer to the default display.
 * 
 * @throw GglException if could not open display
 * @return Pointer to the display
 */
Display* GglWindowGlx::getDefaultDisplay() {
	
	Display *display = XOpenDisplay(NULL);
	
	if (display == NULL) {
		throw GglException("Could not open default display!");
	}
	return display;
}

/**
 * Returns an event mask for use with the window.
 */
long GglWindowGlx::getEventMask() {
	return ExposureMask
			| StructureNotifyMask
			| VisibilityChangeMask
			| KeyPressMask
			| PointerMotionMask;
}

/**
 * Returns a color map for the window.
 */

Colormap GglWindowGlx::getColormap() {
	return XCreateColormap(
				display,
				RootWindow(display, visual->screen),
				visual->visual,
				AllocNone);
}



/**
 * Returns mask for specifying window properties.
 */
long GglWindowGlx::getWindowMask() {
	return CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;
}

XSetWindowAttributes GglWindowGlx::getWindowAttributes() {
	
	XSetWindowAttributes wa;
	
	wa.event_mask = getEventMask();
	wa.border_pixel = 0;
	wa.bit_gravity = StaticGravity;
	wa.colormap = getColormap();
	return wa;
}

/**
 * Returns an X window to back the GGL window.
 */
Window GglWindowGlx::createXWindow() {
	
	int winmask = getWindowMask();
	XSetWindowAttributes wa = getWindowAttributes();
	
	return XCreateWindow(
			display,
			DefaultRootWindow(display),
			0, 0,
			512, 512,
			0,
			visual->depth,
			InputOutput,
			visual->visual,
			winmask,
			&wa);
}
