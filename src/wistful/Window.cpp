/*
 * Window.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "wistful/Window.hpp"
using namespace Wistful;
using namespace std;

/**
 * Creates a window from a format.
 * 
 * @param wf Configuration of window
 */
Wistful::Window::Window(const WindowFormat &wf) {
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
Wistful::Window::~Window() {
    destroy();
}

/**
 * Adds an object that will be notified of events.
 */
void Wistful::Window::addWindowListener(WindowListener *listener) {
    windowListeners.push_back(listener);
}

/**
 * Marks the window as destroyed.
 */
void Wistful::Window::close() {
    doClose();
}

/**
 * Shows a window and begins sending events.
 */
void Wistful::Window::open(Window *window) {
    try {
        window->create();
        window->activate();
        window->run();
        window->destroy();
    } catch (const exception &e) {
        cerr << e.what() << endl;
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
void Wistful::Window::activate() throw(exception) {
    
    // Guard against bad requests
    if (!created || activated || destroyed) {
        return;
    }
    
    // Try to activate objects
    try {
        doActivateContext();
        doActivateWindow();
    } catch (const exception &e) {
        destroy();
        throw WindowException(e.what());
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
void Wistful::Window::create() throw(exception) {
    
    // Guard against bad requests
    if (created || destroyed) {
        return;
    }
    
    // Try to make connection
    doCreateConnection();
    
    // Try to make window
    try {
        doCreateWindow();
    } catch (const exception &e) {
        doDestroyConnection();
        throw;
    }
    
    // Try to make context
    try {
        doCreateContext();
    } catch (const exception &e) {
        doDestroyWindow();
        doDestroyConnection();
        throw;
    }
    
    // Successfully created
    created = true;
}

/**
 * Destroys the window.
 */
void Wistful::Window::destroy() {
    
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
void Wistful::Window::fireKeyEvent(int key) {
    
    list<WindowListener*>::iterator it;
    WindowEvent event(this, key);
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onWindowKey(event);
    }
}

/**
 * Sends a destroy event to all listeners.
 */
void Wistful::Window::fireDestroyEvent() {
    
    list<WindowListener*>::iterator it;
    WindowEvent event(this);
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onWindowClose(event);
    }
}

/**
 * Sends a display event to all listeners.
 */
void Wistful::Window::fireDisplayEvent() {
    
    list<WindowListener*>::iterator it;
    WindowEvent event(this);
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onWindowPaint(event);
    }
    doFlush();
}

/**
 * Sends an initialize event to all listeners.
 */
void Wistful::Window::fireInitEvent() {
    
    list<WindowListener*>::iterator it;
    WindowEvent event(this);
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onWindowOpen(event);
    }
}

/**
 * Initiates the run loop to handle events.
 */
void Wistful::Window::run() {
    doRun();
}

//--------------------------------------------------
// Getters and setters
//

/**
 * Returns size of window on X axis.
 */
int Wistful::Window::getWidth() const {
    return width;
}

/**
 * Returns size of window on Y axis.
 */
int Wistful::Window::getHeight() const {
    return height;
}

/**
 * Changes the size of the window.
 */
void Wistful::Window::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

/**
 * Returns initial location of window on X axis.
 */
int Wistful::Window::getX() const {
    return x;
}

/**
 * Returns initial location of window on Y axis.
 */
int Wistful::Window::getY() const {
    return y;
}

/**
 * Changes the initial location of the window.
 */
void Wistful::Window::setLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

/**
 * Returns copy of configuration used to create window.
 */
WindowFormat
Wistful::Window::getWindowFormat() const {
    return windowFormat;
}
