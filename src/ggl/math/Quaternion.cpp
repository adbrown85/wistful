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

/**
 * Creates a quaternion representing no rotation.
 */
Quaternion::Quaternion() {
    s = 1.0;
    v.set(0.0, 0.0, 0.0);
}

/**
 * Creates a quaternion representing an angle/axis rotation.
 * 
 * @param angle Degrees around axis
 * @param axis Axis of rotation
 */
Quaternion::Quaternion(float angle, const Vec4 &axis) {
    
    float halfAngleInRadians = toRadians(0.5 * angle);
    float magnitude;
    
    // Calculate
    s = cos(halfAngleInRadians);
    v = axis * sin(halfAngleInRadians);
    
    // Normalize
    magnitude = sqrt(s*s + v.x*v.x + v.y*v.y + v.z*v.z);
    s /= magnitude;
    v /= magnitude;
}

/**
 * Rotates the quaternion by an angle/axis rotation.
 * 
 * @param angle Degrees around axis
 * @param axis Axis of rotation
 */
void Quaternion::rotate(float angle, const Vec4 &axis) {
    
    Quaternion q(angle, axis);
    float dp = dot(q.v, v);
    
    v = (v * q.s) + (q.v * s) + cross(q.v, v);
    s = (q.s * s) - dp;
}

/**
 * Returns a matrix corresponding to the quaternion's rotation.
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

/**
 * Returns a string representation of the quaternion.
 */
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

/**
 * Prints a quaternion to standard out.
 * 
 * @param q Quaternion to print
 */
void print(const Quaternion &q) {
    cout << q.toString() << endl;
}

} /* namespace Ggl */
