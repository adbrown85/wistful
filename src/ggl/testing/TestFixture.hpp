/*
 * TestFixture.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TESTFIXTURE_HPP
#define GGL_TESTFIXTURE_HPP
#include <cassert>
#include <cmath>
#include <sstream>
#include "ggl/common.h"
#include "ggl/Exception.hpp"
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
    static void assertEquals(float x, float y, float epsilon);
private:
    static const float DEFAULT_EPSILON = 0.001;
// Helpers
    static std::string createMessage(float x, float y);
};

} // namespace Ggl
#endif
