/*
 * PerspectiveProjection.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/transform/PerspectiveProjection.hpp"
using namespace Ggl;

/**
 * Constructs a perspective projection.
 * 
 * @param fov Field of view angle in Y direction, in degrees
 * @param aspect Aspect ratio of area being rendered to
 * @param near Distance from viewer to near clipping plane
 * @param far Distance from viewer to far clipping plane
 * @throw std::exception if field of view is negative
 * @throw std::exception if aspect ratio is negative
 * @throw std::exception if distance to near clipping plane is negative
 * @throw std::exception if distance to far clipping plane is negative
 */
PerspectiveProjection::PerspectiveProjection(float fov, float aspect,
                                             float near, float far)
        : Projection(near, far) {
    if (fov < 0) {
        throw Exception("Field of view is negative!");
    } else if (aspect < 0) {
        throw Exception("Aspect ratio is negative!");
    } else if (near < 0) {
        throw Exception("Distance to near clipping plane is negative!");
    } else if (far < 0) {
        throw Exception("Distance to far clipping plane is negative!");
    } else {
        this->fieldOfView = fov;
        this->aspectRatio = aspect;
    }
}

/**
 * Destroys the projection.
 */
PerspectiveProjection::~PerspectiveProjection() {
    ;
}

/**
 * Updates the perspective projection to correspond with a viewport.
 * 
 * @param viewport Viewport that was changed
 * @throw std::exception if viewport is NULL
 */
void PerspectiveProjection::onViewportEvent(Viewport *viewport) {
    if (viewport == NULL) {
        throw Exception("Viewport is NULL!");
    } else {
        aspectRatio = (float) viewport->getWidth() / viewport->getHeight();
        fireProjectionEvent();
    }
}

/**
 * Returns a copy of the matrix representing the projection.
 */
Mat4 PerspectiveProjection::toMat4() {
    
    Mat4 mat(1.0);
    float f = 1.0 / tan(toRadians(fieldOfView) / 2);
    float zNear = getNearClippingPlane();
    float zFar = getFarClippingPlane();
    
    mat(0,0) = f / aspectRatio;
    mat(1,1) = f;
    mat(2,2) = (zFar + zNear) / (zNear - zFar);
    mat(2,3) = (2 * zFar * zNear) / (zNear - zFar);
    mat(3,2) = -1;
    
    return mat;
}

/* ACCESSORS AND MUTATORS */

/**
 * Returns the aspect ratio of the projection.
 */
float PerspectiveProjection::getAspectRatio() const {
    return aspectRatio;
}

/**
 * Changes the aspect ratio of the projection.
 * 
 * @param aspect Aspect ratio of area being rendered to
 * @throw std::exception if aspect ratio is negative
 */
void PerspectiveProjection::setAspectRatio(float aspect) {
    if (aspect < 0) {
        throw Exception("Aspect ratio is negative!");
    } else {
        this->aspectRatio = aspect;
    }
}

/**
 * Returns the field of view angle in Y direction in degrees.
 */
float PerspectiveProjection::getFieldOfView() const {
    return fieldOfView;
}

/**
 * Changes the field of view angle in Y direction in degrees.
 * 
 * @param fov Field of view angle in Y direction, in degrees
 * @throw Exception if field of view is negative
 */
void PerspectiveProjection::setFieldOfView(float fov) {
    if (fov < 0) {
        throw Exception("Field of view is negative!");
    } else {
        this->fieldOfView = fov;
    }
}
