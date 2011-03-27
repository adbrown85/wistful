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
