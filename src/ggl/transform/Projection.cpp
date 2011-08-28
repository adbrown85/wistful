/*
 * Projection.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/transform/Projection.hpp"
using namespace Ggl;
using namespace std;

/**
 * Constructs a projection.
 * 
 * @param near Distance from viewer to near clipping plane
 * @param far Distance from viewer to far clipping plane
 */
Projection::Projection(float near, float far) {
    this->nearClippingPlane = near;
    this->farClippingPlane = far;
}

/**
 * Destroys the projection.
 */
Projection::~Projection() {
    ;
}

/**
 * Registers a listener with the projection.
 * 
 * @param listener Observer of projection events to register
 * @throw std::exception if listener is NULL
 */
void Projection::addProjectionListener(ProjectionListener *listener) {
    if (listener == NULL) {
        throw Exception("Listener is NULL!");
    } else {
        listeners.push_back(listener);
    }
}

/**
 * Unregisters a listener with the projection.
 * 
 * @param listener Observer of projection events to unregister
 * @throw std::exception if listener is NULL
 */
void Projection::removeProjectionListener(ProjectionListener *listener) {
    if (listener == NULL) {
        throw Exception("Listener is NULL!");
    } else {
        listeners.remove(listener);
    }
}

/* ACCESSORS AND MUTATORS */

/**
 * Returns distance to near clipping plane.
 */
float Projection::getNearClippingPlane() const {
    return nearClippingPlane;
}

/**
 * Returns distance to far clipping plane.
 */
float Projection::getFarClippingPlane() const {
    return farClippingPlane;
}

/**
 * Changes the near and far clipping planes.
 * 
 * @param near Distance from viewer to near clipping plane
 * @param far Distance from viewer to far clipping plane
 * @throw std::exception if near clipping plane greater than far
 */
void Projection::setNearFarClippingPlanes(float near, float far) {
    if (near > far) {
        throw Exception("Near clipping plane is greater than far!");
    } else {
        this->nearClippingPlane = near;
        this->farClippingPlane = far;
        fireProjectionEvent();
    }
}

/* HELPERS */

/**
 * Sends a projection event to each registered listener.
 */
void Projection::fireProjectionEvent() {
    
    list<ProjectionListener*>::iterator it;
    
    for (it=listeners.begin(); it!=listeners.end(); ++it) {
        (*it)->onProjectionEvent(this);
    }
}
