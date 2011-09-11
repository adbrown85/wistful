/*
 * Mat4Test.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MAT4TEST_HXX
#define GGL_MAT4TEST_HXX
#include "ggl/common.h"
#include <edo/TestFixture.hpp>
#include <edo/TestRunner.hpp>
#include "ggl/math/Mat4.hpp"
namespace Ggl {


/**
 * Unit test for Mat4.
 */
class Mat4Test : public Edo::TestFixture {
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
