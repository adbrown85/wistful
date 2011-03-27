/*
 * GglWindowGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowGlx.hpp"

/** Creates a window for GLX. */
GglWindowGlx::GglWindowGlx() {
	this->display = NULL;
	this->info = NULL;
	this->window = NULL;
	this->context = NULL;
}

/** Destroys the window. */
GglWindowGlx::~GglWindowGlx() {
	;
}

/** Shows the window. */
void GglWindowGlx::doOpen() {
	
	GglConfigGlx *config = createConfig();
	
	display = getDefaultDisplay();
	info = glXGetVisualFromFBConfig(display, config->getFBConfig());
	
	createXWindow();
	mapXWindow();
	
	context = glXCreateContext(display, info, 0, True);
	glXMakeCurrent(display, window, context);
	
	glViewport(0, 0, 512, 512);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glXSwapBuffers(display, window);
}

/**
 * Closes the window.
 */
void GglWindowGlx::doClose() {
    glXDestroyContext(display, context);
    context = NULL;
	XDestroyWindow(display, window);
	window = NULL;
	XCloseDisplay(display);
	display = NULL;
}

//---------------------------------------------------------
// Helpers
//

/**
 * Returns an OpenGL configuration for use with the window. 
 */
GglConfigGlx* GglWindowGlx::createConfig() {
	
	GglConfigFactory cf;
	map<int,int> reqs;
	
	reqs[GLX_X_RENDERABLE] = 1;
	reqs[GLX_DRAWABLE_TYPE] = GLX_WINDOW_BIT;
	reqs[GLX_RENDER_TYPE] = GLX_RGBA_BIT;
	reqs[GLX_CONFIG_CAVEAT] = GLX_NONE;
	reqs[GLX_DOUBLEBUFFER] = 1;
	reqs[GLX_RED_SIZE] = 8;
	reqs[GLX_GREEN_SIZE] = 8;
	reqs[GLX_BLUE_SIZE] = 8;
	reqs[GLX_ALPHA_SIZE] = 8;
	
	return (GglConfigGlx*) cf.create(reqs);
}

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
				RootWindow(display, info->screen),
				info->visual,
				AllocNone);
}

/**
 * Returns mask for specifying window properties.
 */
long GglWindowGlx::getWindowMask() {
	return CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;
}

/**
 * Return window attributes needed to create backing X window.
 */
XSetWindowAttributes GglWindowGlx::getWindowAttributes() {
	
	XSetWindowAttributes wa;
	
	wa.event_mask = getEventMask();
	wa.border_pixel = 0;
	wa.bit_gravity = StaticGravity;
	wa.colormap = getColormap();
	return wa;
}

/**
 * Makes an X window to back the GGL window.
 */
void GglWindowGlx::createXWindow() {
	
	int winmask = getWindowMask();
	XSetWindowAttributes wa = getWindowAttributes();
	
	window = XCreateWindow(
			display,
			DefaultRootWindow(display),
			0, 0,
			512, 512,
			0,
			info->depth,
			InputOutput,
			info->visual,
			winmask,
			&wa);
}

/**
 * Shows the X window on a screen.
 */
void GglWindowGlx::mapXWindow() {
	
    XEvent event;
    
	XMapWindow(display, window);
    XSelectInput(display, window, StructureNotifyMask);
	XNextEvent(display, &event);
    while (event.type != MapNotify) {
    	XNextEvent(display, &event);
    }
}
