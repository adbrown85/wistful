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
    this->created = false;
    this->destroyed = false;
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->x = DEFAULT_X;
    this->y = DEFAULT_Y;
    this->closed = false;
}

/**
 * Destroys the window.
 */
GglWindow::~GglWindow() {
    destroy();
}

/**
 * Adds an object that will be notified of events.
 */
void GglWindow::addListener(GglListener *listener) {
    listeners.push_back(listener);
}

/**
 * Marks the window as destroyed.
 */
void GglWindow::close() {
    closed = true;
}

/**
 * Shows a window and begins sending events.
 */
void GglWindow::open(GglWindow *window) {
    window->create();
    window->run();
    window->destroy();
}

//--------------------------------------------------
// Helpers
//

/**
 * Creates the window.
 * 
 * @throw GglException if cannot make connection to windowing system
 * @throw GglException if cannot make native window
 * @throw GglException if cannot make OpenGL context
 */
void GglWindow::create() {
    
    // Guard against bad requests
    if (created || destroyed) {
        return;
    }
    
    // Try to make objects
    createConnection();
    createWindow();
    createContext();
    
    // Set up OpenGL
    glViewport(0, 0, getWidth(), getHeight());
    
    // Successfully shown
    created = true;
}

/**
 * Makes a connection to the windowing system.
 * 
 * @throw GglException if could not make connection
 */
void GglWindow::createConnection() throw(GglException) {
    try {
        doCreateConnection();
    } catch (GglException &e) {
        throw GglException("Could not make connection to windowing system!");
    }
}

/**
 * Makes and activates a native window.
 * 
 * @throw GglException if window could not be made
 */
void GglWindow::createWindow() throw(GglException) {
    try {
        doCreateWindow();
        doActivateWindow();
    } catch (GglException &e) {
        doDestroyConnection();
        throw GglException("Could not make native window!");
    }
}

/**
 * Makes and activates an OpenGL context.
 * 
 * @throw GglException if context could not be made
 */
void GglWindow::createContext() throw(GglException) {
    try {
        doCreateContext();
        doActivateContext();
    } catch (GglException &e) {
        doDestroyWindow();
        doDestroyConnection();
        throw GglException("Could not make OpenGL context!");
    }
}

/**
 * Destroys the window.
 */
void GglWindow::destroy() {
    
    // Guard against bad requests
    if (!created || destroyed) {
        return;
    }
    
    // Destroy everything
    doDestroyContext();
    doDestroyWindow();
    doDestroyConnection();
    
    // Successfully closed
    destroyed = true;
}

/**
 * Sends a key event to all listeners.
 */
void GglWindow::fireKeyEvent(GglEvent &event) {
    
    list<GglListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->onKey((*this), event);
    }
}

/**
 * Sends a destroy event to all listeners.
 */
void GglWindow::fireDestroyEvent() {
    
    list<GglListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->onDestroy((*this));
    }
}

/**
 * Sends a display event to all listeners.
 */
void GglWindow::fireDisplayEvent() {
    
    list<GglListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->onDisplay((*this));
    }
    doFlush();
}

/**
 * Sends an initialize event to all listeners.
 */
void GglWindow::fireInitEvent() {
    
    list<GglListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->onInit((*this));
    }
}

/**
 * Initiates the run loop to handle events.
 */
void GglWindow::run() {
    doRun();
}

//--------------------------------------------------
// Getters and setters
//

/**
 * Returns size of window on X axis.
 */
int GglWindow::getWidth() const {
    return width;
}

/**
 * Returns size of window on Y axis.
 */
int GglWindow::getHeight() const {
    return height;
}

/**
 * Changes the size of the window.
 */
void GglWindow::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

/**
 * Returns initial location of window on X axis.
 */
int GglWindow::getX() const {
    return x;
}

/**
 * Returns initial location of window on Y axis.
 */
int GglWindow::getY() const {
    return y;
}

/**
 * Changes the initial location of the window.
 */
void GglWindow::setLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

/**
 * Returns <tt>true</tt> if window has been destroyed.
 */
bool GglWindow::isClosed() const {
    return closed;
}
