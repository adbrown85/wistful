/*
 * GglWindow.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/GglWindow.hpp"

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
    doClose();
}

/**
 * Shows a window and begins sending events.
 */
void GglWindow::open(GglWindow *window) {
    try {
        window->create();
        window->activate();
        window->run();
        window->destroy();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

//--------------------------------------------------
// Helpers
//

/**
 * Shows the window.
 * 
 * @throw std::exception if cannot activate native window
 * @throw std::exception if cannot activate OpenGL context
 */
void GglWindow::activate() throw(std::exception) {
    
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
 * @throw std::exception if cannot make connection to windowing system
 * @throw std::exception if cannot make native window
 * @throw std::exception if cannot make OpenGL context
 */
void GglWindow::create() throw(std::exception) {
    
    // Guard against bad requests
    if (created || destroyed) {
        return;
    }
    
    // Try to make connection
    doCreateConnection();
    
    // Try to make window
    try {
        doCreateWindow();
    } catch (std::exception &e) {
        doDestroyConnection();
        throw e;
    }
    
    // Try to make context
    try {
        doCreateContext();
    } catch (std::exception &e) {
        doDestroyWindow();
        doDestroyConnection();
        throw e;
    }
    
    // Successfully created
    created = true;
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
 * Returns copy of configuration used to create window.
 */
GglWindowFormat
GglWindow::getWindowFormat() const {
    return windowFormat;
}
