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
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
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
 * Shows a window and begins sending events.
 */
void GglWindow::run(GglWindow *window) {
    
    bool destroyed = false;
    
    window->open();
    while (!destroyed) {
        GglEvent event = window->doGetEvent();
        switch (event.getType()) {
        case MAP:
            window->fireInitEvent();
            break;
        case EXPOSE:
            window->fireDisplayEvent();
            break;
        case DESTROY:
            window->fireDestroyEvent();
            destroyed = true;
            break;
        case KEY:
            window->fireKeyEvent(event);
            break;
        default:
            continue;
        }
    }
    window->close();
    cerr << "End of GglWindow::run()" << endl;
}

//--------------------------------------------------
// Helpers
//

/**
 * Closes the window.
 */
void GglWindow::close() {
    
    // Guard against bad closes
    if (!opened || closed) {
        return;
    }
    
    // Destroy everything
    doDestroyContext();
    doDestroyWindow();
    doDestroyConnection();
    
    // Successfully closed
    closed = true;
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
 * Sends a key event to all listeners.
 */
void GglWindow::fireKeyEvent(GglEvent &event) {
    
    list<GglListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->onKey(event);
    }
}

/**
 * Sends a destroy event to all listeners.
 */
void GglWindow::fireDestroyEvent() {
    
    list<GglListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->destroy();
    }
}

/**
 * Sends a display event to all listeners.
 */
void GglWindow::fireDisplayEvent() {
    
    list<GglListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->display();
    }
    doFlush();
}

/**
 * Sends an initialize event to all listeners.
 */
void GglWindow::fireInitEvent() {
    
    list<GglListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->init();
    }
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
    
    // Try to make objects
    createConnection();
    createWindow();
    createContext();
    
    // Set up OpenGL
    glViewport(0, 0, 512, 512);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    doFlush();
    
    // Successfully opened
    opened = true;
}

//--------------------------------------------------
// Getters and setters
//

/** Changes the size of the window. */
void GglWindow::setSize(int width, int height) {
    this->width = width;
    this->height = height;
}

/** Returns size of window on X axis. */
int GglWindow::getWidth() {
    return width;
}

/** Returns size of window on Y axis. */
int GglWindow::getHeight() {
    return height;
}
