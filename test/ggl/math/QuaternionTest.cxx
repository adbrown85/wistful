/*
 * QuaternionTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/math/QuaternionTest.hxx"
using namespace std;
using namespace Edo;
using namespace Ggl;

const float QuaternionTest::ANGLE_30 = toRadians(30);
const float QuaternionTest::ANGLE_45 = toRadians(45);

void QuaternionTest::testToMat4() {
    
    q = Quaternion::fromAxisAngle(Vec4(0,1,0), ANGLE_45);
    mat = q.toMat4();
    
    assertEquals( 0.707, mat(0,0));
    assertEquals( 0.000, mat(0,1));
    assertEquals( 0.707, mat(0,2));
    assertEquals( 0.000, mat(0,3));
    assertEquals( 0.000, mat(1,0));
    assertEquals( 1.000, mat(1,1));
    assertEquals( 0.000, mat(1,2));
    assertEquals( 0.000, mat(1,3));
    assertEquals(-0.707, mat(2,0));
    assertEquals( 0.000, mat(2,1));
    assertEquals( 0.707, mat(2,2));
    assertEquals( 0.000, mat(2,3));
    assertEquals( 0.000, mat(3,0));
    assertEquals( 0.000, mat(3,1));
    assertEquals( 0.000, mat(3,2));
    assertEquals( 1.000, mat(3,3));
}

void QuaternionTest::testRotate() {
    
    q = Quaternion::fromAxisAngle(Vec4(0,1,0), ANGLE_30);
    q.rotate(Vec4(0,1,0), ANGLE_45);
    mat = q.toMat4();
    
    assertEquals( 0.259, mat(0,0));
    assertEquals( 0.000, mat(0,1));
    assertEquals( 0.966, mat(0,2));
    assertEquals( 0.000, mat(0,3));
    assertEquals( 0.000, mat(1,0));
    assertEquals( 1.000, mat(1,1));
    assertEquals( 0.000, mat(1,2));
    assertEquals( 0.000, mat(1,3));
    assertEquals(-0.966, mat(2,0));
    assertEquals( 0.000, mat(2,1));
    assertEquals( 0.259, mat(2,2));
    assertEquals( 0.000, mat(2,3));
    assertEquals( 0.000, mat(3,0));
    assertEquals( 0.000, mat(3,1));
    assertEquals( 0.000, mat(3,2));
    assertEquals( 1.000, mat(3,3));
}

/*
 * Runs the test.
 */
#define EDO_TEST_FIXTURE QuaternionTest
EDO_TEST_SUITE
EDO_ADD_TEST(testToMat4)
EDO_ADD_TEST(testRotate)
EDO_RUN_TESTS

