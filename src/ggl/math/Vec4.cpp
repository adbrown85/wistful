/*
 * Vec4.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/math/Vec4.hpp"
using namespace Ggl;
using namespace Edo;
using namespace std;

/**
 * Creates an empty vector with one for the homogeneous coordinate.
 */
Vec4::Vec4() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 1.0;
}

/**
 * Creates a vector from values with one for the homogeneous coordinate.
 * 
 * @param x Value for X component
 * @param y Value for Y component
 * @param z Value for Z component
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
 * @param x Value for X component
 * @param y Value for Y component
 * @param z Value for Z component
 * @param w Value for homogeneous coordinate
 */
Vec4::Vec4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

/**
 * Copies the values of another vector to this vector.
 * 
 * Notes:
 *  - Homogeneous coordinate is copied
 * 
 * @param v Vector to copy
 * @return Reference to this vector
 */
Vec4& Vec4::operator=(const Vec4 &v) {
    
    // Check for self-assignment
    if (this == &v) {
        return *this;
    }
    
    // Set components
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

/**
 * Adds another vector to this vector.
 * 
 * Notes:
 *  - Homogeneous coordinate is ignored
 * 
 * @param v Vector with values to add
 * @return Reference to this vector
 */
Vec4& Vec4::operator+=(const Vec4 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

/**
 * Subtracts another vector from this vector.
 * 
 * Notes:
 *  - Homogeneous coordinate is ignored
 * 
 * @param v Vector with values to subtract
 * @return Reference to this vector
 */
Vec4& Vec4::operator-=(const Vec4 &v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

/**
 * Multiplies this vector by another vector.
 * 
 * Notes:
 *  - Homogeneous coordinate is ignored
 * 
 * @param v Vector with values to multiply by
 * @return Reference to this vector
 */
Vec4& Vec4::operator*=(const Vec4 &v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

/**
 * Divides this vector by another vector.
 * 
 * Notes:
 *  - Homogeneous coordinate is ignored
 * 
 * @param v Vector with values to divide by
 * @return Reference to this vector
 */
Vec4& Vec4::operator/=(const Vec4 &v) {
    if ((v.x == 0) || (v.y == 0) || (v.z == 0)) {
        throw Exception("[Vec4] Cannot divide by zero!");
    } else {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    
}

/**
 * Adds a value to this vector.
 * 
 * Notes:
 *  - Homogeneous coordinate is ignored
 * 
 * @param f Value to add
 * @return Reference to this vector
 */
Vec4& Vec4::operator+=(float f) {
    x += f;
    y += f;
    z += f;
    return *this;
}

/**
 * Subtracts a value from this vector.
 * 
 * Notes:
 *  - Homogeneous coordinate is ignored
 * 
 * @param f Value to subtract
 * @return Reference to this vector
 */
Vec4& Vec4::operator-=(float f) {
    x -= f;
    y -= f;
    z -= f;
    return *this;
}

/**
 * Multiplies this vector by a value.
 * 
 * Notes:
 *  - Homogeneous coordinate is ignored
 * 
 * @param f Value to multiply by
 * @return Reference to this vector
 */
Vec4& Vec4::operator*=(float f) {
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

/**
 * Divides this vector by a value.
 * 
 * Notes:
 *  - Homogeneous coordinate is ignored
 * 
 * @param f Value to divide by
 * @return Reference to this vector
 * @throw std::exception if would divide by zero
 */
Vec4& Vec4::operator/=(float f) {
    if (f == 0) {
        throw Exception("[Vec4] Cannot divide by zero!");
    } else {
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }
    
}

/**
 * Checks if two vectors are equal.
 * 
 * Notes:
 *  - Homogeneous coordinate is checked
 * 
 * @param u First vector to check
 * @param v Second vector to check
 * @return <tt>true</tt> if vectors are equals
 */
bool operator==(const Vec4 &u, const Vec4 &v) {
    return (u.x == v.x) && (u.y == v.y) && (u.z == v.z) && (u.w == v.w);
}

/**
 * Adds a vector to another vector.
 * 
 * Notes:
 *  - Copies homogeneous coordinate of first vector
 * 
 * @param u Vector to add to
 * @param v Vector to add
 * @return Copy of resulting vector
 */
Vec4 operator+(const Vec4 &u, const Vec4 &v) {
    return Vec4((u.x + v.x), (u.y + v.y), (u.z + v.z), u.w);
}

/**
 * Subtracts a vector from another vector.
 * 
 * Notes:
 *  - Copies homogeneous coordinate of first vector
 * 
 * @param u Vector to subtract from
 * @param v Vector to subtract
 * @return Copy of resulting vector
 */
Vec4 operator-(const Vec4 &u, const Vec4 &v) {
    return Vec4((u.x - v.x), (u.y - v.y), (u.z - v.z), u.w);
}

/**
 * Multiplies a vector by another vector.
 * 
 * Notes:
 *  - Copies homogeneous coordinate of first vector
 * 
 * @param u Vector to multiply
 * @param v Vector to multiply by
 * @return Copy of resulting vector
 */
Vec4 operator*(const Vec4 &u, const Vec4 &v) {
    return Vec4((u.x * v.x), (u.y * v.y), (u.z * v.z), u.w);
}

/**
 * Divides a vector by another vector.
 * 
 * Notes:
 *  - Copies homogeneous coordinate of first vector
 * 
 * @param u Vector to divide
 * @param v Vector to divide by
 * @return Copy of resulting vector
 * @throw std::exception if would divide by zero
 */
Vec4 operator/(const Vec4 &u, const Vec4 &v) {
    if ((v.x == 0) || (v.y == 0) || (v.z == 0)) {
        throw Exception("[Vec4] Cannot divide by zero!");
    } else {
        return Vec4((u.x / v.x), (u.y / v.y), (u.z / v.z), u.w);
    }
}

/**
 * Adds a value to a vector.
 * 
 * Notes:
 *  - Copies homogeneous coordinate of vector
 * 
 * @param u Vector to add to
 * @param f Value to add
 * @return Copy of resulting vector
 */
Vec4 operator+(const Vec4 &u, float f) {
    return Vec4((u.x + f), (u.y + f), (u.z + f), u.w);
}

/**
 * Subtracts a value from a vector.
 * 
 * Notes:
 *  - Copies homogeneous coordinate of vector
 * 
 * @param u Vector to subtract from
 * @param f Value to subtract
 * @return Copy of resulting vector
 */
Vec4 operator-(const Vec4 &u, float f) {
    return Vec4((u.x - f), (u.y - f), (u.z - f), u.w);
}

/**
 * Multiplies a vector by a value.
 * 
 * Notes:
 *  - Copies homogeneous coordinate of vector
 * 
 * @param u Vector to multiply
 * @param f Value to multiply by
 * @return Copy of resulting vector
 */
Vec4 operator*(const Vec4 &u, float f) {
    return Vec4((u.x * f), (u.y * f), (u.z * f), u.w);
}

/**
 * Divides a vector by a value.
 * 
 * Notes:
 *  - Copies homogeneous coordinate of vector
 * 
 * @param u Vector to divide
 * @param f Value to divide by
 * @return Copy of resulting vector
 * @throw std::exception if would divide by zero
 */
Vec4 operator/(const Vec4 &u, float f) {
    if (f == 0) {
        throw Exception("[Vec4] Cannot divide by zero!");
    } else {
        return Vec4((u.x / f), (u.y / f), (u.z / f), u.w);
    }
}

/**
 * Appends a vector to a stream.
 * 
 * @param out Stream to append to
 * @param u Vector to append
 * @return Reference to the stream
 */
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
 * Accesses a component in the vector by index.
 * 
 * @param i Index of component
 * @return Reference to the component
 * @throw std::exception if the index is out of bounds.
 */
float& Vec4::operator[](int i) {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
        throw Exception("[Vec4] Index out of bounds!");
    }
}

/**
 * Accesses a component in the vector by index.
 * 
 * @param i Index of component
 * @return Copy of the component
 * @throw std::exception if the index is out of bounds.
 */
float Vec4::operator[](int i) const {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
        throw Exception("[Vec4] Index out of bounds!");
    }
}

/**
 * Computes the cross product of two vectors.
 * 
 * Notes:
 *  - Uses one for the homogeneous coordinate
 * 
 * @param u First vector
 * @param v Second vector
 * @return vector perpendicular to the plane formed by two vectors
 */
Vec4 cross(const Vec4 &u, const Vec4 &v) {
    
    float x = (u.y * v.z) - (u.z * v.y);
    float y = (u.z * v.x) - (u.x * v.z);
    float z = (u.x * v.y) - (u.y * v.x);
    
    return Vec4(x, y, z, 1.0);
}

/**
 * Computes the dot product of two vectors.
 * 
 * Notes:
 *  - Ignores the homogeneous coordinate
 * 
 * @param u First vector
 * @param v Second vector
 * @return projection of one vector onto another
 */
float dot(const Vec4 &u, const Vec4 &v) {
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

/**
 * Accesses a component of the vector.
 * 
 * @param i Index of component
 * @return Copy of the component's value
 * @throw std::exception if index out of bounds.
 */
float Vec4::get(int i) const {
    switch (i) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    case 3: return w;
    default:
        throw Exception("[Vec4] Index out of bounds!");
    }
}

/**
 * Calculates the length of the vector.
 * 
 * Notes:
 *  - Ignores the homogeneous coordinate
 * 
 * @return Length of the vector
 */
float Vec4::length() const {
    return sqrt((x * x) + (y * y) + (z * z));
}

/**
 * Computes a component-wise maximum of two vectors.
 * 
 * Notes:
 *  - Uses one for the homogeneous coordinate
 * 
 * @param u First vector
 * @param v Second vector
 * @return Copy of resulting vector
 */
Vec4 max(const Vec4 &u, const Vec4 &v) {
    return Vec4(max(u.x, v.x), max(u.y, v.y), max(u.z, v.z));
}

/**
 * Computes a component-wise minimum of two vectors.
 * 
 * Notes:
 *  - Uses one for the homogeneous coordinate
 * 
 * @param u First vector
 * @param v Second vector
 * @return Copy of resulting vector
 */
Vec4 min(const Vec4 &u, const Vec4 &v) {
    return Vec4(min(u.x, v.x), min(u.y, v.y), min(u.z, v.z));
}

/**
 * Converts a vector to a unit-length vector.
 * 
 * Notes:
 *  - Copies the homogeneous coordinate
 * 
 * @param u Vector to convert
 * @return Copy of resulting vector
 */
Vec4 normalize(const Vec4 &u) {
    
    float len = u.length();
    
    // Divide by length
    if (len == 0.0) {
        return Vec4();
    } else {
        return Vec4((u.x / len), (u.y / len), (u.z / len), u.w);
    }
}

/**
 * Changes the values of a vector.
 * 
 * @param x Value for X component
 * @param y Value for Y component
 * @param z Value for Z component
 */
void Vec4::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

/**
 * Changes the values of a vector.
 * 
 * @param x Value for X component
 * @param y Value for Y component
 * @param z Value for Z component
 * @param w Value for homogeneous coordinate
 */
void Vec4::set(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

/**
 * Converts a vector to an array.
 * 
 * @param array Existing float array
 */
void Vec4::toArray(float array[4]) {
    array[0] = x;
    array[1] = y;
    array[2] = z;
    array[3] = w;
}
