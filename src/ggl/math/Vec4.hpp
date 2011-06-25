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
#include "ggl/Exception.hpp"
namespace Ggl {


/**
 * @brief Four-component vector with dot and cross product capabilities.
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
public:
    friend bool operator==(const Vec4 &u, const Vec4 &v);
    friend Vec4 operator+(const Vec4 &u, const Vec4 &v);
    friend Vec4 operator-(const Vec4 &u, const Vec4 &v);
    friend Vec4 operator*(const Vec4 &u, const Vec4 &v);
    friend Vec4 operator/(const Vec4 &u, const Vec4 &v);
    friend Vec4 operator+(const Vec4 &u, float f);
    friend Vec4 operator-(const Vec4 &u, float f);
    friend Vec4 operator*(const Vec4 &u, float f);
    friend Vec4 operator/(const Vec4 &u, float f);
    friend std::ostream& operator<<(std::ostream& out, const Vec4& u);
    friend Vec4 cross(const Vec4& u, const Vec4& v);
    friend float dot(const Vec4& u, const Vec4 &v);
    friend Vec4 min(const Vec4 &u, const Vec4 &v);
    friend Vec4 max(const Vec4 &u, const Vec4 &v);
    friend Vec4 normalize(const Vec4 &u);
};

} // namespace Ggl
#endif
