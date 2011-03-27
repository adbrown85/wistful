/*
 * GglWindow.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindow.hpp"

/** Creates a window for GLX. */
GglWindowGlx::GglWindowGlx(GglConfigGlx *cfg) {
	display = XOpenDisplay(NULL);
	visualInfo = glXGetVisualFromFBConfig(display, cfg->getFBConfig());
}

/** Destroys the window. */
GglWindowGlx::~GglWindowGlx() {
	XDestroyWindow(display, window);
	XCloseDisplay(display);
}

/** Shows the window. */
void GglWindowGlx::show() {
	
	XSetWindowAttributes wa;
	
	wa.event_mask = 
			ExposureMask | VisibilityChangeMask | 
			KeyPressMask | PointerMotionMask | 
			StructureNotifyMask;
	wa.border_pixel = 0;
	wa.bit_gravity = StaticGravity;
	wa.colormap = XCreateColormap(
			display,
			RootWindow(display, visualInfo->screen),
			visualInfo->visual,
			AllocNone);
	int winmask = CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;
	
	window = XCreateWindow(
			display,
			DefaultRootWindow(display),
			0, 0,
			512, 512,
			0,
			visualInfo->depth,
			InputOutput,
			visualInfo->visual,
			winmask,
			&wa);
	XMapWindow(display, window);
	
	GLXContext context = glXCreateContext(display, visualInfo, 0, True);
	glXMakeCurrent(display, window, context);
	
	glViewport(0, 0, 512, 512);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glXSwapBuffers(display, window);
}
