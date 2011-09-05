/*
 * PerspectiveProjection.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PERSPECTIVEPROJECTION_HPP
#define GGL_PERSPECTIVEPROJECTION_HPP
#include "ggl/common.h"
#include "ggl/math/Math.hpp"
#include "ggl/transform/Projection.hpp"
#include "ggl/transform/Viewport.hpp"
namespace Ggl {


/**
 * @brief Projection that causes items farther back to appear smaller.
 */
class PerspectiveProjection : public Projection {
public:
    PerspectiveProjection(float fov, float aspect, float near, float far);
    virtual ~PerspectiveProjection();
    virtual void onViewportEvent(Viewport *viewport);
    virtual Mat4 toMat4();
// Accessors
    float getAspectRatio() const;
    void setAspectRatio(float aspect);
    float getFieldOfView() const;
    void setFieldOfView(float fov);
private:
    float fieldOfView;
    float aspectRatio;
};

} /* namespace Ggl */
#endif
