/*
 * Math.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/math/Math.hpp"
using namespace std;
using namespace Ggl;

/**
 * Converts degrees to radians.
 * 
 * @param degrees Number of degrees to convert
 * @return Value in radians
 */
double toRadians(double degrees) {
    return degrees * (PI / 180);
}
