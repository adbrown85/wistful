/*
 * Vec4.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_VEC4_HPP
#define GGL_VEC4_HPP
#include "ggl/common.h"
#include <cmath>
#include <iomanip>
namespace Ggl {


/**
 * Four-component vector for 3D graphics.
 * 
 * <p><i>Vec4</i> is a four-component vector for use with 3D graphics.
 * It includes an extra homogeneous coordinate, which is often used in
 * perspective transformations and allows the vector to be easily
 * multiplied by a four-by-four matrix.  However, generally the
 * programmer wishes to keep the homogeneous coordinate value equal to
 * one.  For that reason, most <i>Vec4</i> operations ignore it or
 * explicitly set it equal to one.  See the documentation for specific
 * methods for details.
 * 
 * @ingroup math
 */
class Vec4 {
public:
    float x;
    float y;
    float z;
    float w;
public:
    Vec4();
    Vec4(float x, float y, float z);
    Vec4(float x, float y, float z, float w);
    Vec4& operator=(const Vec4 &v);
    Vec4& operator+=(const Vec4 &v);
    Vec4& operator-=(const Vec4 &v);
    Vec4& operator*=(const Vec4 &v);
    Vec4& operator/=(const Vec4 &v);
    Vec4& operator+=(float f);
    Vec4& operator-=(float f);
    Vec4& operator*=(float f);
    Vec4& operator/=(float f);
    float& operator[](int i);
    float operator[](int i) const;
    float length() const;
    float get(int i) const;
    void set(float x, float y, float z);
    void set(float x, float y, float z, float w);
    void toArray(float array[4]);
};

} // namespace Ggl

bool operator==(const Ggl::Vec4 &u, const Ggl::Vec4 &v);
Ggl::Vec4 operator+(const Ggl::Vec4 &u, const Ggl::Vec4 &v);
Ggl::Vec4 operator-(const Ggl::Vec4 &u, const Ggl::Vec4 &v);
Ggl::Vec4 operator*(const Ggl::Vec4 &u, const Ggl::Vec4 &v);
Ggl::Vec4 operator/(const Ggl::Vec4 &u, const Ggl::Vec4 &v);
Ggl::Vec4 operator+(const Ggl::Vec4 &u, float f);
Ggl::Vec4 operator-(const Ggl::Vec4 &u, float f);
Ggl::Vec4 operator*(const Ggl::Vec4 &u, float f);
Ggl::Vec4 operator/(const Ggl::Vec4 &u, float f);
std::ostream& operator<<(std::ostream& out, const Ggl::Vec4& u);
Ggl::Vec4 cross(const Ggl::Vec4& u, const Ggl::Vec4& v);
float dot(const Ggl::Vec4& u, const Ggl::Vec4 &v);
Ggl::Vec4 min(const Ggl::Vec4 &u, const Ggl::Vec4 &v);
Ggl::Vec4 max(const Ggl::Vec4 &u, const Ggl::Vec4 &v);
Ggl::Vec4 normalize(const Ggl::Vec4 &u);
#endif
