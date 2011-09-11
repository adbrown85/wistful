/*
 * QuaternionTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef QUATERNIONTEST_HXX
#define QUATERNIONTEST_HXX
#include "ggl/common.h"
#include <edo/TestRunner.hpp>
#include "ggl/math/Quaternion.hpp"
namespace Ggl {


/**
 * @brief Unit test for Quaternion.
 */
class QuaternionTest : public Edo::TestFixture {
public:
    void testToMat4();
    void testRotate();
private:
    Quaternion q;
    Mat4 mat;
// Constants
    static const float ANGLE_45;
    static const float ANGLE_30;
};

} /* namespace Ggl */
#endif
