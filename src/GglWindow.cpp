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
 * Shows the window on the screen.
 */
void GglWindow::open() {
	if (!opened && !closed) {
		doOpen();
		opened = true;
	}
}

/**
 * Clears the window from the screen.
 */
void GglWindow::close() {
	if (opened && !closed) {
		doClose();
		closed = true;
	}
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
