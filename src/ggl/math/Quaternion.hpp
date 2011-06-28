/*
 * Quaternion.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_QUATERNION_HPP
#define GGL_QUATERNION_HPP
#include "ggl/common.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include "ggl/math/Math.hpp"
#include "ggl/math/Mat4.hpp"
#include "ggl/math/Vec4.hpp"
namespace Ggl {


/**
 * @brief Encapsulation of an axis/angle rotation.
 */
class Quaternion {
public:
    Quaternion();
    Quaternion(float angle, const Vec4 &axis);
    Quaternion operator*(const Quaternion &B);
    void set(float angle, const Vec4 &axis);
    void rotate(float angle, const Vec4 &axis);
    Mat4 toMat4() const;
    std::string toString() const;
private:
    float s;
    Vec4 v;
// Helpers
    void normalize();
};

void print(const Quaternion &q);

} /* namespace Ggl */

#endif
