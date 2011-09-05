/*
 * PreprocessorTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PREPROCESSORTEST_HXX
#define GGL_PREPROCESSORTEST_HXX
#define GGL_TEST_FIXTURE PreprocessorTest
#include "ggl/common.h"
#include "ggl/shader/Preprocessor.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
namespace Ggl {


/**
 * @brief Unit test for Preprocessor.
 */
class PreprocessorTest : public TestFixture {
public:
    void testParse();
};

} /* namespace Ggl */
#endif
