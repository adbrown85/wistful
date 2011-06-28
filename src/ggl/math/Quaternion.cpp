/*
 * Quaternion.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Quaternion.hpp"
using namespace std;
using namespace Ggl;
namespace Ggl {

Quaternion::Quaternion() {
    s = 1.0;
    v.set(0.0, 0.0, 0.0);
}

Quaternion::Quaternion(float angle, const Vec4 &axis) {
    set(angle, axis);
}

void Quaternion::normalize() {
    
    float mag;
    
    // Divide by magnitude
    mag = sqrt(s*s + v.x*v.x + v.y*v.y + v.z*v.z);
    s /= mag;
    v /= mag;
}

void Quaternion::rotate(float angle, const Vec4 &axis) {
    
    Quaternion q(angle, axis);
    float dp = dot(q.v, v);
    
    v = (v * q.s) + (q.v * s) + cross(q.v, v);
    s = (q.s * s) - dp;
}

void Quaternion::set(float angle, const Vec4 &axis) {
    
    float halfAngleInRadians = toRadians(0.5 * angle);
    
    // Calculate
    s = cos(halfAngleInRadians);
    v = axis * sin(halfAngleInRadians);
    
    // Normalize
    normalize();
}

/**
 * Returns a matrix representing the rotation.
 */
Mat4 Quaternion::toMat4() const {
    
    float xx2 = v.x * v.x * 2;
    float yy2 = v.y * v.y * 2;
    float zz2 = v.z * v.z * 2;
    float xy2 = v.x * v.y * 2;
    float xz2 = v.x * v.z * 2;
    float yz2 = v.y * v.z * 2;
    float sx2 = s * v.x * 2;
    float sy2 = s * v.y * 2;
    float sz2 = s * v.z * 2;
    Mat4 C;
    
    // Calculate matrix
    C(0,0) = 1.0 - yy2 - zz2;
    C(0,1) = xy2 - sz2;
    C(0,2) = xz2 + sy2;
    C(1,0) = xy2 + sz2;
    C(1,1) = 1.0 - xx2 - zz2;
    C(1,2) = yz2 - sx2;
    C(2,0) = xz2 - sy2;
    C(2,1) = yz2 + sx2;
    C(2,2) = 1.0 - xx2 - yy2;
    C(3,3) = 1.0;
    
    return C;
}

string Quaternion::toString() const {
    
    stringstream stream;
    
    // Make string
    stream << "Quaternion"
           << " s='" << s << "'"
           << " x='" << v.x << "'"
           << " y='" << v.y << "'"
           << " z='" << v.z << "'";
    return stream.str();
}

void print(const Quaternion &q) {
    cout << "  " << q.toString() << endl;
}

} /* namespace Ggl */
