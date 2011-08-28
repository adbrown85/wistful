/*
 * Projection.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PROJECTION_HPP
#define GGL_PROJECTION_HPP
#include "ggl/common.h"
#include "ggl/Exception.hpp"
#include "ggl/math/Mat4.hpp"
namespace Ggl {


/**
 * Delegate for calculating a projection matrix.
 */
class Projection : public ViewportListener {
public:
    Projection(float near, float far);
    virtual ~Projection();
    virtual void addProjectionListener(ProjectionListener *listener);
    virtual void removeProjectionListener(ProjectionListener *listener);
    virtual void onViewportEvent(Viewport *viewport) = 0;
    virtual Mat4 toMat4() = 0;
// Accessors
    virtual float getNearClippingPlane() const;
    virtual float getFarClippingPlane() const;
    virtual void setNearFarClippingPlanes(float near, float far);
protected:
    void fireProjectionEvent();
private:
    float nearClippingPlane;
    float farClippingPlane;
    std::list<ProjectionListener*> listeners;
};

} /* namespace Ggl */
#endif
