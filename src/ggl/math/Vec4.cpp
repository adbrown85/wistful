/*
 * Vec4.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/math/Vec4.hpp"
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
 * Four-component vector.
 */
Vec4::Vec4(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 1.0;
}

/**
 * Four-component vector.
 */
Vec4::Vec4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vec4& Vec4::operator=(const Vec4 &B) {
    
    // Check for self-assignment
    if (this == &B)
        return *this;
    
    // Set components
    x = B.x;
    y = B.y;
    z = B.z;
    w = B.w;
    return *this;
}

Vec4& Vec4::operator+=(const Vec4 &B) {
    x += B.x;
    y += B.y;
    z += B.z;
    w += B.w;
    return *this;
}

Vec4& Vec4::operator-=(const Vec4 &B) {
    x -= B.x;
    y -= B.y;
    z -= B.z;
    w -= B.w;
    return *this;
}

Vec4& Vec4::operator*=(const Vec4 &B) {
    x *= B.x;
    y *= B.y;
    z *= B.z;
    w *= B.w;
    return *this;
}

Vec4& Vec4::operator/=(const Vec4 &B) {
    x /= B.x;
    y /= B.y;
    z /= B.z;
    w /= B.w;
    return *this;
}

Vec4& Vec4::operator+=(float b) {
    x += b;
    y += b;
    z += b;
    w += b;
    return *this;
}

Vec4& Vec4::operator-=(float b) {
    x -= b;
    y -= b;
    z -= b;
    w -= b;
    return *this;
}

Vec4& Vec4::operator*=(float b) {
    x *= b;
    y *= b;
    z *= b;
    w *= b;
    return *this;
}

Vec4& Vec4::operator/=(float b) {
    
    float bInv=1/b;
    
    x *= bInv;
    y *= bInv;
    z *= bInv;
    w *= bInv;
    return *this;
}

bool operator==(const Vec4 &A, const Vec4 &B) {
    return (A.x==B.x) && (A.y==B.y) && (A.z==B.z) && (A.w==B.w);
}

Vec4 operator+(const Vec4 &A, const Vec4 &B) {
    
    Vec4 C;
    
    C.x = A.x + B.x;
    C.y = A.y + B.y;
    C.z = A.z + B.z;
    C.w = A.w + B.w;
    
    return C;
}

Vec4 operator-(const Vec4 &A, const Vec4 &B) {
    
    Vec4 C;
    
    C.x = A.x - B.x;
    C.y = A.y - B.y;
    C.z = A.z - B.z;
    C.w = A.w - B.w;
    
    return C;
}

Vec4 operator*(const Vec4 &A, const Vec4 &B) {
    
    Vec4 C;
    
    C.x = A.x * B.x;
    C.y = A.y * B.y;
    C.z = A.z * B.z;
    C.w = A.w * B.w;
    
    return C;
}

Vec4 operator/(const Vec4 &A, const Vec4 &B) {
    
    Vec4 C;
    
    if (B.x != 0)
        C.x = A.x / B.x;
    if (B.y != 0)
        C.y = A.y / B.y;
    if (B.z != 0)
        C.z = A.z / B.z;
    if (B.w != 0)
        C.w = A.w / B.w;
    
    return C;
}

Vec4 operator+(const Vec4 &A, float b) {
    return Vec4(A.x+b, A.y+b, A.z+b, A.w+b);
}

Vec4 operator-(const Vec4 &A, float b) {
    return Vec4(A.x-b, A.y-b, A.z-b, A.w-b);
}

Vec4 operator*(const Vec4 &A, float b) {
    
    Vec4 C;
    
    C.x = A.x * b;
    C.y = A.y * b;
    C.z = A.z * b;
    C.w = A.w * b;
    
    return C;
}

Vec4 operator/(const Vec4 &A, float b) {
    
    Vec4 C;
    
    if (b != 0) {
        C.x = A.x / b;
        C.y = A.y / b;
        C.z = A.z / b;
        C.w = A.w / b;
    }
    
    return C;
}

ostream& operator<<(ostream &out, const Vec4 &A) {
    out << fixed << setprecision(2);
    out << "[";
    out << A.x << "," << A.y << "," << A.z << "," << A.w;
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
        throw Ggl::Exception("[Vector] Index out of bounds.");
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
        throw Ggl::Exception("[Vector] Index out of bounds.");
    }
}

/**
 * @return vector perpendicular to the plane formed by two vectors.
 */
Vec4 cross(const Vec4 &A, const Vec4 &B) {
    
    Vec4 C;
    
    C.x = (A.y * B.z) - (A.z * B.y);
    C.y = (A.z * B.x) - (A.x * B.z);
    C.z = (A.x * B.y) - (A.y * B.x);
    C.w = 1.0;
    
    return C;
}

/**
 * @return projection of one vector onto another.
 */
float dot(const Vec4 &A, const Vec4 &B) {
    return A.x*B.x + A.y*B.y + A.z*B.z;
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
        throw Ggl::Exception("[Vector] Index out of bounds.");
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
Vec4 max(const Vec4 &A, const Vec4 &B) {
    return Vec4(max(A.x,B.x), max(A.y,B.y), max(A.z,B.z), max(A.w,B.w));
}

/**
 * @return component-wise minimum of the two vectors
 */
Vec4 min(const Vec4 &A, const Vec4 &B) {
    return Vec4(min(A.x,B.x), min(A.y,B.y), min(A.z,B.z), min(A.w,B.w));
}

/**
 * @return Unit length version of the vector.
 */
Vec4 normalize(Vec4 vector) {
    
    float len;
    
    // Divide by length
    len = vector.length();
    if (len == 0.0) {
        vector = Vec4();
    } else {
        vector /= len;
        vector.w = 1.0;
    }
    return vector;
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
