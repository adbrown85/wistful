/*
 * BitmapReaderTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_BITMAPREADERTEST_HXX
#define GGL_BITMAPREADERTEST_HXX
#define GGL_TEST_FIXTURE BitmapReaderTest
#include "ggl/common.h"
#include "ggl/image/BitmapReader.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
namespace Ggl {


/**
 * @brief Unit test for BitmapReader.
 */
class BitmapReaderTest : public TestFixture {
public:
    BitmapReaderTest();
    void testGetters();
    void testToImage();
private:
    BitmapReader reader;
};

} /* namespace Ggl */
#endif
