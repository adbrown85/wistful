/*
 * QuaternionTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/common.h"
#include "ggl/math/Quaternion.hpp"
#include "ggl/testing/TestRunner.hpp"
using namespace std;
using namespace Ggl;

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

void QuaternionTest::testToMat4() {
    
    q = Quaternion(45, Vec4(0,1,0));
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
    
    q = Quaternion(30, Vec4(0,1,0));
    q.rotate(45, Vec4(0,1,0));
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
#define GGL_TEST_FIXTURE QuaternionTest
GGL_TEST_SUITE
GGL_ADD_TEST(testToMat4)
GGL_ADD_TEST(testRotate)
GGL_RUN_TESTS

