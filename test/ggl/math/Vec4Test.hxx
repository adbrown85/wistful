/*
 * Vec4Test.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_VEC4TEST_HXX
#define GGL_VEC4TEST_HXX
#include "ggl/common.h"
#include <edo/TestFixture.hpp>
#include <edo/TestRunner.hpp>
#include "ggl/math/Vec4.hpp"
namespace Ggl {


/**
 * @brief Unit test for Vec4.
 */
class Vec4Test : public Edo::TestFixture {
public:
    void setUp();
    void testAdd();
    void testSubtract();
    void testMultiply();
    void testDivide();
private:
    Vec4 A, B, C;
};

} /* namespace Ggl */
#endif
