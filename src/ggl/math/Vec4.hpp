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
    Vec4& operator=(const Vec4 &B);
    Vec4& operator+=(const Vec4 &B);
    Vec4& operator-=(const Vec4 &B);
    Vec4& operator*=(const Vec4 &B);
    Vec4& operator/=(const Vec4 &B);
    Vec4& operator+=(float b);
    Vec4& operator-=(float b);
    Vec4& operator*=(float b);
    Vec4& operator/=(float b);
    float& operator[](int i);
    float operator[](int i) const;
    float length() const;
    float get(int i) const;
    void set(float x, float y, float z);
    void set(float x, float y, float z, float w);
    void toArray(float array[4]);
public:
    friend bool operator==(const Vec4 &A, const Vec4 &B);
    friend Vec4 operator+(const Vec4 &A, const Vec4 &B);
    friend Vec4 operator-(const Vec4 &A, const Vec4 &B);
    friend Vec4 operator*(const Vec4 &A, const Vec4 &B);
    friend Vec4 operator/(const Vec4 &A, const Vec4 &B);
    friend Vec4 operator+(const Vec4 &A, float b);
    friend Vec4 operator-(const Vec4 &A, float b);
    friend Vec4 operator*(const Vec4 &A, float b);
    friend Vec4 operator/(const Vec4 &A, float b);
    friend std::ostream& operator<<(std::ostream& out, const Vec4& A);
    friend Vec4 cross(const Vec4& A, const Vec4& B);
    friend float dot(const Vec4& A, const Vec4 &B);
    friend Vec4 min(const Vec4 &A, const Vec4 &B);
    friend Vec4 max(const Vec4 &A, const Vec4 &B);
    friend Vec4 normalize(Vec4 vector);
};


#endif
