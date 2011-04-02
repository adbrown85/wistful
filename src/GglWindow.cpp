/*
 * GglWindow.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindow.hpp"

/**
 * Creates a window.
 */
GglWindow::GglWindow() {
	this->opened = false;
	this->closed = false;
}

/**
 * Destroys the window.
 */
GglWindow::~GglWindow() {
	close();
}

/**
 * Adds an object that will be notified of events.
 */
void GglWindow::addListener(GglListener *listener) {
	listeners.push_back(listener);
}

/**
 * Opens the window.
 * 
 * @throw GglException if cannot make connection to windowing system
 * @throw GglException if cannot make native window
 * @throw GglException if cannot make OpenGL context
 */
void GglWindow::open() {
	
	// Guard against bad opens
	if (opened || closed) {
		return;
	}
	
	// Try to make connection
	if (!doCreateConnection()) {
		throw GglException("Could not make connection to windowing system!");
	}
	
	// Try to make window
	if (!doCreateWindow()) {
	    doDestroyConnection();
		throw GglException("Could not make native window!");
	}
	doActivateWindow();
	
	// Try to make context
	if (!doCreateContext()) {
	    doDestroyConnection();
	    doDestroyWindow();
		throw GglException("Could not make OpenGL context!");
	}
	doActivateContext();
	
	// Set up OpenGL
    glViewport(0, 0, 512, 512);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    doFlush();
    
    // Successfully opened
	opened = true;
}

/**
 * Closes the window.
 */
void GglWindow::close() {
	
	// Guard against bad closes
	if (!opened || closed) {
		return;
	}
	
	// Destroy everything
	doDestroyConnection();
	doDestroyWindow();
	doDestroyContext();
	
	// Successfully closed
	closed = true;
}

/**
 * Shows a window and begins sending events.
 */
void GglWindow::run(GglWindow *window) {
	
	bool destroyed = false;
	
	window->open();
	while (!destroyed) {
		GglEvent event = window->doGetEvent();
		switch (event.getType()) {
		case DESTROY:
			destroyed = true;
			break;
		default:
			continue;
		}
	}
	window->close();
	cerr << "End of GglWindow::run()" << endl;
}
