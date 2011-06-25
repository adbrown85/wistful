/*
 * Vec4.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/math/Vec4.hpp"
using namespace Ggl;
using namespace std;

/**
 * Creates an empty vector with a default homogeneous coordinate.
 */
Vec4::Vec4() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 1.0;
}

/**
 * Creates a vector with explicit values and a default homogeneous coordinate.
 * 
 * @param x Value on X axis
 * @param y Value on Y axis
 * @param z Value on Z axis
 */
Vec4::Vec4(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 1.0;
}

/**
 * Creates a vector with explicit values.
 * 
 * @param x Value on X axis
 * @param y Value on Y axis
 * @param z Value on Z axis
 * @param w Value for homogeneous coordinate
 */
Vec4::Vec4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4& Vec4::operator=(const Vec4 &v) {
    
    // Check for self-assignment
    if (this == &v)
        return *this;
    
    // Set components
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

Vec4& Vec4::operator+=(const Vec4 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

Vec4& Vec4::operator-=(const Vec4 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

Vec4& Vec4::operator*=(const Vec4 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
}

Vec4& Vec4::operator/=(const Vec4 &v) {
    
    // Check for division by zero
    if ((v.x == 0) || (v.y == 0) || (v.z == 0) || (v.w == 0)) {
        throw Exception("Cannot divide by zero!");
    }
    
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
}

Vec4& Vec4::operator+=(float f) {
    x += f;
    y += f;
    z += f;
    w += f;
    return *this;
}

Vec4& Vec4::operator-=(float f) {
    x -= f;
    y -= f;
    z -= f;
    w -= f;
    return *this;
}

Vec4& Vec4::operator*=(float f) {
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
}

Vec4& Vec4::operator/=(float f) {
    
    float fInv;
    
    // Check for division by zero
    if (f == 0) {
        throw Exception("Cannot divide by zero!");
    }
    
    fInv = 1/f;
    x *= fInv;
    y *= fInv;
    z *= fInv;
    w *= fInv;
    return *this;
}

bool operator==(const Vec4 &u, const Vec4 &v) {
    return (u.x==v.x) && (u.y==v.y) && (u.z==v.z) && (u.w==v.w);
}

Vec4 operator+(const Vec4 &u, const Vec4 &v) {
    
    Vec4 C;
    
    C.x = u.x + v.x;
    C.y = u.y + v.y;
    C.z = u.z + v.z;
    C.w = u.w + v.w;
    
    return C;
}

Vec4 operator-(const Vec4 &u, const Vec4 &v) {
    
    Vec4 C;
    
    C.x = u.x - v.x;
    C.y = u.y - v.y;
    C.z = u.z - v.z;
    C.w = u.w - v.w;
    
    return C;
}

Vec4 operator*(const Vec4 &u, const Vec4 &v) {
    
    Vec4 C;
    
    C.x = u.x * v.x;
    C.y = u.y * v.y;
    C.z = u.z * v.z;
    C.w = u.w * v.w;
    
    return C;
}

Vec4 operator/(const Vec4 &u, const Vec4 &v) {
    
    Vec4 C;
    
    if ((v.x == 0) || (v.y == 0) || (v.z == 0) || (v.w == 0)) {
        throw Exception("Cannot divide by zero!");
    }
    
    C.x = u.x / v.x;
    C.y = u.y / v.y;
    C.z = u.z / v.z;
    C.w = u.w / v.w;
    
    return C;
}

Vec4 operator+(const Vec4 &u, float f) {
    return Vec4(u.x+f, u.y+f, u.z+f, u.w+f);
}

Vec4 operator-(const Vec4 &u, float f) {
    return Vec4(u.x-f, u.y-f, u.z-f, u.w-f);
}

Vec4 operator*(const Vec4 &u, float f) {
    
    Vec4 C;
    
    C.x = u.x * f;
    C.y = u.y * f;
    C.z = u.z * f;
    C.w = u.w * f;
    
    return C;
}

Vec4 operator/(const Vec4 &u, float f) {
    
    Vec4 C;
    
    // Check for division by zero
    if (f == 0) {
        throw Exception("[Vec4] Cannot divide by zero!");
    }
    
    C.x = u.x / f;
    C.y = u.y / f;
    C.z = u.z / f;
    C.w = u.w / f;
    
    return C;
}

ostream& operator<<(ostream &out, const Vec4 &u) {
    out << fixed << setprecision(2);
    out << "[";
    out << u.x << "," << u.y << "," << u.z << "," << u.w;
    out << "]";
    out << resetiosflags(ios_base::floatfield);
    out << setprecision(6);
    return out;
}

/**
 * @throw Exception if the index is out of bounds.
 */
float& Vec4::operator[](int i) {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
        throw Exception("[Vector] Index out of bounds.");
    }
}

/**
 * @throw BasicException if the index is out of bounds.
 */
float Vec4::operator[](int i) const {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
        throw Exception("[Vector] Index out of bounds.");
    }
}

/**
 * @return vector perpendicular to the plane formed by two vectors.
 */
Vec4 cross(const Vec4 &u, const Vec4 &v) {
    
    Vec4 C;
    
    C.x = (u.y * v.z) - (u.z * v.y);
    C.y = (u.z * v.x) - (u.x * v.z);
    C.z = (u.x * v.y) - (u.y * v.x);
    C.w = 1.0;
    
    return C;
}

/**
 * @return projection of one vector onto another.
 */
float dot(const Vec4 &u, const Vec4 &v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

/**
 * @throw BasicException if index out of bounds.
 */
float Vec4::get(int i) const {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
        throw Exception("[Vector] Index out of bounds.");
    }
}

/**
 * @return length of the vector.
 */
float Vec4::length() const {
    return sqrt(x*x + y*y + z*z);
}

/**
 * @return component-wise maximum of the two vectors
 */
Vec4 max(const Vec4 &u, const Vec4 &v) {
    return Vec4(max(u.x,v.x), max(u.y,v.y), max(u.z,v.z), max(u.w,v.w));
}

/**
 * @return component-wise minimum of the two vectors
 */
Vec4 min(const Vec4 &u, const Vec4 &v) {
    return Vec4(min(u.x,v.x), min(u.y,v.y), min(u.z,v.z), min(u.w,v.w));
}

/**
 * @return Unit length version of the vector.
 */
Vec4 normalize(Vec4 u) {
    
    float len;
    
    // Divide by length
    len = u.length();
    if (len == 0.0) {
        u = Vec4();
    } else {
        u /= len;
        u.w = 1.0;
    }
    return u;
}

void Vec4::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vec4::set(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Vec4::toArray(float array[4]) {
    array[0] = x;
    array[1] = y;
    array[2] = z;
    array[3] = w;
}
