/*
 * Window.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/Window.hpp"
using namespace Ggl;
using namespace std;

/**
 * Creates a window from a format.
 * 
 * @param wf Configuration of window
 */
Ggl::Window::Window(const WindowFormat &wf) {
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
Ggl::Window::~Window() {
    destroy();
}

/**
 * Adds an object that will be notified of events.
 */
void Ggl::Window::addWindowListener(WindowListener *listener) {
    windowListeners.push_back(listener);
}

/**
 * Marks the window as destroyed.
 */
void Ggl::Window::close() {
    doClose();
}

/**
 * Shows a window and begins sending events.
 */
void Ggl::Window::open(Window *window) {
    try {
        window->create();
        window->activate();
        window->run();
        window->destroy();
    } catch (exception &e) {
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
void Ggl::Window::activate() throw(exception) {
    
    // Guard against bad requests
    if (!created || activated || destroyed) {
        return;
    }
    
    // Try to activate objects
    try {
        doActivateContext();
        doActivateWindow();
    } catch (exception &e) {
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
void Ggl::Window::create() throw(exception) {
    
    // Guard against bad requests
    if (created || destroyed) {
        return;
    }
    
    // Try to make connection
    doCreateConnection();
    
    // Try to make window
    try {
        doCreateWindow();
    } catch (exception &e) {
        doDestroyConnection();
        throw e;
    }
    
    // Try to make context
    try {
        doCreateContext();
    } catch (exception &e) {
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
void Ggl::Window::destroy() {
    
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
void Ggl::Window::fireKeyEvent(int key) {
    
    list<WindowListener*>::iterator it;
    WindowEvent event(this, key);
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onKey(this, event);
    }
}

/**
 * Sends a destroy event to all listeners.
 */
void Ggl::Window::fireDestroyEvent() {
    
    list<WindowListener*>::iterator it;
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onDestroy(this);
    }
}

/**
 * Sends a display event to all listeners.
 */
void Ggl::Window::fireDisplayEvent() {
    
    list<WindowListener*>::iterator it;
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onDisplay(this);
    }
    doFlush();
}

/**
 * Sends an initialize event to all listeners.
 */
void Ggl::Window::fireInitEvent() {
    
    list<WindowListener*>::iterator it;
    
    for (it=windowListeners.begin(); it!=windowListeners.end(); ++it) {
        (*it)->onInit(this);
    }
}

/**
 * Initiates the run loop to handle events.
 */
void Ggl::Window::run() {
    doRun();
}

//--------------------------------------------------
// Getters and setters
//

/**
 * Returns size of window on X axis.
 */
int Ggl::Window::getWidth() const {
    return width;
}

/**
 * Returns size of window on Y axis.
 */
int Ggl::Window::getHeight() const {
    return height;
}

/**
 * Changes the size of the window.
 */
void Ggl::Window::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

/**
 * Returns initial location of window on X axis.
 */
int Ggl::Window::getX() const {
    return x;
}

/**
 * Returns initial location of window on Y axis.
 */
int Ggl::Window::getY() const {
    return y;
}

/**
 * Changes the initial location of the window.
 */
void Ggl::Window::setLocation(int x, int y) {
    this->x = x;
    this->y = y;
}

/**
 * Returns copy of configuration used to create window.
 */
WindowFormat
Ggl::Window::getWindowFormat() const {
    return windowFormat;
}
