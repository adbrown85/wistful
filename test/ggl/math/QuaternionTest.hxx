/*
 * QuaternionTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef QUATERNIONTEST_HXX
#define QUATERNIONTEST_HXX
#define GGL_TEST_FIXTURE QuaternionTest
#include "ggl/common.h"
#include "ggl/math/Quaternion.hpp"
#include "ggl/testing/TestRunner.hpp"
namespace Ggl {


/**
 * @brief Unit test for Quaternion.
 */
class QuaternionTest : public TestFixture {
public:
    void testToMat4();
    void testRotate();
private:
    Mat4 mat;
    Quaternion q;
};

} /* namespace Ggl */
#endif
