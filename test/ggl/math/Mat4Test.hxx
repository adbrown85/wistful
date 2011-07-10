/*
 * Mat4Test.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MAT4TEST_HXX
#define GGL_MAT4TEST_HXX
#define GGL_TEST_FIXTURE Mat4Test
#include "ggl/common.h"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
#include "ggl/math/Mat4.hpp"
namespace Ggl {


/**
 * @brief Unit test for Mat4.
 */
class Mat4Test : public TestFixture {
public:
    void setUp();
    void testInverse();
    void testMultiplyTime();
    void testSetArray();
    void testTranspose();
    void testMultiplyVector();
private:
    Mat4 m1, m2, m3;
};



} /* namespace Ggl */
#endif
