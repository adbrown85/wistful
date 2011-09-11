/*
 * OrthographicProjection.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/transform/OrthographicProjection.hpp"
using namespace Edo;
using namespace Ggl;

/**
 * Constructs an orthographic projection.
 * 
 * @param left World coordinate of left clipping plane
 * @param right World coordinate of right clipping plane
 * @param bottom World coordinate of bottom clipping plane
 * @param top World coordinate of top clipping plane
 * @param near Distance from viewer to near clipping plane
 * @param far Distance from viewer to far clipping plane
 * @throw std::exception if left clipping plane is >= right
 * @throw std::exception if bottom clipping plane is >= top
 */
OrthographicProjection::OrthographicProjection(float left, float right,
                                               float bottom, float top,
                                               float near, float far)
        : Projection(near, far) {
    if (left >= right) {
        throw Exception("Left >= right!");
    } else if (bottom >= top) {
        throw Exception("Bottom >= top!");
    } else if (near >= far) {
        throw Exception("Near >= far!");
    } else {
        this->leftClippingPlane = left;
        this->rightClippingPlane = right;
        this->bottomClippingPlane = bottom;
        this->topClippingPlane = top;
    }
}

/**
 * Destroys the orthographic projection.
 */
OrthographicProjection::~OrthographicProjection() {
    ;
}

/**
 * Updates the orthographic projection to correspond with a viewport.
 * 
 * @param viewport Viewport that was changed
 * @throw std::exception if viewport is NULL
 */
void OrthographicProjection::onViewportEvent(Viewport *viewport) {
    if (viewport == NULL) {
        throw Exception("Viewport is NULL!");
    } else {
        leftClippingPlane = viewport->getX();
        rightClippingPlane = viewport->getX() + viewport->getWidth();
        bottomClippingPlane = viewport->getY();
        topClippingPlane = viewport->getY() + viewport->getHeight();
        fireProjectionEvent();
    }
}

/**
 * Returns a copy of the matrix representing the projection.
 */
Mat4 OrthographicProjection::toMat4() {
    
    Mat4 mat(1);
    float width = rightClippingPlane - leftClippingPlane;
    float height = topClippingPlane - bottomClippingPlane;
    float depth = getFarClippingPlane() - getNearClippingPlane();
    float tx = - ((rightClippingPlane + leftClippingPlane) / width);
    float ty = - ((topClippingPlane + bottomClippingPlane) / height);
    float tz = - ((getFarClippingPlane() + getNearClippingPlane()) / depth);
    
    // Scale
    mat(0,0) = 2.0 / width;
    mat(1,1) = 2.0 / height;
    mat(2,2) = -2.0 / depth;
    mat(3,3) = 1;
    
    // Translate
    mat(0,3) = tx;
    mat(1,3) = ty;
    mat(2,3) = tz;
    
    return mat;
}

/* ACCESSORS AND MUTATORS */

/**
 * Returns world coordinate of left clipping plane.
 */
float OrthographicProjection::getLeftClippingPlane() const {
    return leftClippingPlane;
}

/**
 * Returns world coordinate of right clipping plane.
 */
float OrthographicProjection::getRightClippingPlane() const {
    return rightClippingPlane;
}

/**
 * Changes the left and right clipping planes.
 * 
 * @param left World coordinate of left clipping plane
 * @param right World coordinate of right clipping plane
 * @throw std::exception if left clipping plane >= right
 */
void
OrthographicProjection::setLeftRightClippingPlanes(float left, float right) {
    if (left >= right) {
        throw Exception("Left >= right!");
    } else {
        this->leftClippingPlane = left;
        this->rightClippingPlane = right;
    }
}

/**
 * Returns world coordinate of bottom clipping plane.
 */
float OrthographicProjection::getBottomClippingPlane() const {
    return bottomClippingPlane;
}

/**
 * Returns world coordinate of top clipping plane.
 */
float OrthographicProjection::getTopClippingPlane() const {
    return topClippingPlane;
}

/**
 * Changes the bottom and top clipping planes.
 * 
 * @param bottom World coordinate of bottom clipping plane
 * @param top World coordinate of top clipping plane
 * @throw std::exception if bottom clipping plane >= top
 */
void
OrthographicProjection::setBottomTopClippingPlanes(float bottom, float top) {
    if (bottom >= top) {
        throw Exception("Bottom >= top!");
    } else {
        this->bottomClippingPlane = bottom;
        this->topClippingPlane = top;
    }
}

