/*
 * Viewport.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/transform/Viewport.hpp"
using namespace Ggl;
using namespace Edo;
using namespace std;

/**
 * Constructs a default viewport.
 */
Viewport::Viewport() {
    this->x = DEFAULT_X;
    this->y = DEFAULT_Y;
    this->width = DEFAULT_WIDTH;
    this->height = DEFAULT_HEIGHT;
}

/**
 * Constructs a viewport from window measurements.
 * 
 * @param x Left side of window area in window pixels
 * @param y Bottom of window area in window pixels
 * @param width Size of window area on X axis in window pixels
 * @param height Size of window area on Y axis in window pixels
 * @throw std::exception if x or y is negative
 * @throw std::exception if width or height is negative
 */
Viewport::Viewport(int x, int y, int width, int height) {
    if (x < 0) {
        throw Exception("X is negative!");
    } else if (y < 0) {
        throw Exception("Y is negative!");
    } else if (width < 0) {
        throw Exception("Width is negative!");
    } else if (height < 0) {
        throw Exception("Height is negative!");
    } else {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
}

/**
 * Destroys the viewport.
 */
Viewport::~Viewport() {
    ;
}

/**
 * Registers a listener with the viewport.
 * 
 * @param listener Observer of viewport events to register
 * @throw Exception if listener is NULL
 */
void Viewport::addViewportListener(ViewportListener *listener) {
    if (listener == NULL) {
        throw Exception("Listener is NULL!");
    } else {
        listeners.push_back(listener);
    }
}

/**
 * Unregisters a listener with the viewport.
 * 
 * @param listener Observer of viewport events to unregister
 * @throw Exception if listener is NULL
 */
void Viewport::removeViewportListener(ViewportListener *listener) {
    if (listener == NULL) {
        throw Exception("Listener is NULL!");
    } else {
        listeners.remove(listener);
    }
}

/**
 * Converts the viewport to an array.
 * 
 * @param arr Array to store values in
 */
void Viewport::toArray(int arr[4]) const {
    arr[0] = x;
    arr[1] = y;
    arr[2] = width;
    arr[3] = height;
}

/* ACCESSORS AND MUTATORS */

/**
 * Returns left side of window area in window pixels.
 */
int Viewport::getX() const {
    return x;
}

/**
 * Returns bottom of window area in window pixels.
 */
int Viewport::getY() const {
    return y;
}

/**
 * Changes the location of the window area.
 * 
 * @param x Left side of window area in window pixels
 * @param y Bottom of window area in window pixels
 * @throw std::exception if x or y is negative
 */
void Viewport::setLocation(int x, int y) {
    if (x < 0) {
        throw Exception("X is negative!");
    } else if (y < 0) {
        throw Exception("Y is negative!");
    } else {
        this->x = x;
        this->y = y;
        fireViewportEvent();
    }
}

/**
 * Returns size of window area on X axis in window pixels.
 */
int Viewport::getWidth() const {
    return width;
}

/**
 * Returns size of window area on Y axis in window pixels.
 */
int Viewport::getHeight() const {
    return height;
}

/**
 * Changes the size of the window area.
 * 
 * @param width Size of window area on X axis in pixels
 * @param height Size of window area on Y axis in pixels
 * @throw std::exception if width or height is negative
 */
void Viewport::setSize(int width, int height) {
    if (width < 0) {
        throw Exception("Width is negative!");
    } else if (height < 0) {
        throw Exception("Height is negative!");
    } else {
        this->width = width;
        this->height = height;
        fireViewportEvent();
    }
}

/* HELPERS */

/**
 * Sends a viewport event to each registered listener.
 */
void Viewport::fireViewportEvent() {
    
    list<ViewportListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->onViewportEvent(this);
    }
}
