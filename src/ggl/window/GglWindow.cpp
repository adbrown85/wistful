/*
 * GglWindow.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/GglWindow.hpp"

/**
 * Creates a window.
 */
GglWindow::GglWindow() {
    this->activated = false;
    this->created = false;
    this->destroyed = false;
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->x = DEFAULT_X;
    this->y = DEFAULT_Y;
    this->closed = false;
}

/**
 * Creates a window from a format.
 * 
 * @param wf Configuration of window
 */
GglWindow::GglWindow(const GglWindowFormat &wf) {
    this->activated = false;
    this->created = false;
    this->destroyed = false;
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
    this->x = DEFAULT_X;
    this->y = DEFAULT_Y;
    this->closed = false;
    this->windowFormat = wf;
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
void GglWindow::addWindowListener(GglWindowListener *listener) {
    windowListeners.push_back(listener);
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
    window->activate();
    window->run();
    window->destroy();
}

//--------------------------------------------------
// Helpers
//

/**
 * Shows the window.
 * 
 * @throw GglException if cannot activate native window
 * @throw GglException if cannot activate OpenGL context
 */
void GglWindow::activate() throw(GglException) {
    
    // Guard against bad requests
    if (!created || activated || destroyed) {
        return;
    }
    
    // Try to activate objects
    try {
        doActivateContext();
        doActivateWindow();
    } catch (std::exception &e) {
        destroy();
        throw e;
    }
    
    // Successfully activated
    activated = true;
}

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
    
    // Successfully created
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
 * Makes a native window.
 * 
 * @throw GglException if window could not be made
 */
void GglWindow::createWindow() throw(GglException) {
    try {
        doCreateWindow();
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
void GglWindow::fireKeyEvent(GglWindowEvent &event) {
    
    std::list<GglWindowListener*>::iterator it;
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onKey(this, event);
    }
}

/**
 * Sends a destroy event to all listeners.
 */
void GglWindow::fireDestroyEvent() {
    
    std::list<GglWindowListener*>::iterator it;
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onDestroy(this);
    }
}

/**
 * Sends a display event to all listeners.
 */
void GglWindow::fireDisplayEvent() {
    
    std::list<GglWindowListener*>::iterator it;
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onDisplay(this);
    }
    doFlush();
}

/**
 * Sends an initialize event to all listeners.
 */
void GglWindow::fireInitEvent() {
    
    std::list<GglWindowListener*>::iterator it;
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onInit(this);
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

/**
 * Returns copy of configuration used to create window.
 */
GglWindowFormat
GglWindow::getWindowFormat() const {
    return windowFormat;
}
