/*
 * OrthographicProjection.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_ORTHOGRAPHICPROJECTION_HPP
#define GGL_ORTHOGRAPHICPROJECTION_HPP
#include "ggl/common.h"
#include "ggl/transform/Projection.hpp"
namespace Ggl {


/**
 * @brief Projection that keeps items at their true size.
 * 
 * @ingroup transform
 */
class OrthographicProjection : public Projection {
public:
    OrthographicProjection(float, float, float, float, float, float);
    virtual ~OrthographicProjection();
    virtual void onViewportEvent(Viewport *viewport);
    virtual Mat4 toMat4();
// Accessors and mutators
    float getLeftClippingPlane() const;
    float getRightClippingPlane() const;
    void setLeftRightClippingPlanes(float left, float right);
    float getBottomClippingPlane() const;
    float getTopClippingPlane() const;
    void setBottomTopClippingPlanes(float bottom, float top);
private:
    float leftClippingPlane;      // World coordinate of left clipping plane
    float rightClippingPlane;     // World coordinate of right clipping plane
    float bottomClippingPlane;    // World coordinate of bottom clipping plane
    float topClippingPlane;       // World coordinate of top clipping plane
};

} /* namespace Ggl */
#endif
