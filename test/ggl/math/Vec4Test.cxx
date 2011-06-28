/*
 * Vec4Test.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/common.h"
#include "ggl/math/Vec4.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
using namespace std;
using namespace Ggl;


/**
 * @brief Unit test for Vec4.
 */
class Vec4Test : public TestFixture {
public:
    void setUp();
    void testAdd();
    void testSubtract();
    void testMultiply();
    void testDivide();
private:
    Vec4 A, B, C;
};

void Vec4Test::setUp() {
    A.set(2, 2, 2);
    B.set(2, 4, 5);
}

void Vec4Test::testAdd() {
    
    C = A + B;
    assertEquals(4, C.x);
    assertEquals(6, C.y);
    assertEquals(7, C.z);
}

void Vec4Test::testSubtract() {
    
    C = A - B;
    assertEquals( 0, C.x);
    assertEquals(-2, C.y);
    assertEquals(-3, C.z);
}

void Vec4Test::testMultiply() {
    
    C = A * B;
    assertEquals( 4, C.x);
    assertEquals( 8, C.y);
    assertEquals(10, C.z);
}

void Vec4Test::testDivide() {
    
    C = A / B;
    assertEquals(1.0, C.x);
    assertEquals(0.5, C.y);
    assertEquals(0.4, C.z);
}

#define GGL_TEST_FIXTURE Vec4Test
GGL_TEST_SUITE
GGL_ADD_TEST(testAdd)
GGL_ADD_TEST(testSubtract)
GGL_ADD_TEST(testMultiply)
GGL_ADD_TEST(testDivide)
GGL_RUN_TESTS
