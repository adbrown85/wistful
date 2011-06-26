/*
 * TestFixture.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TESTFIXTURE_HPP
#define GGL_TESTFIXTURE_HPP
#include "ggl/common.h"
#include <cassert>
#include <cmath>
namespace Ggl {


/**
 * @brief Utility for testing a class.
 */
class TestFixture {
public:
    TestFixture();
    virtual ~TestFixture();
    virtual void setUp();
    virtual void tearDown();
protected:
    static void assertEquals(float x, float y);
private:
    static const float EPSILON = 0.0001;
};

} // namespace Ggl
#endif
