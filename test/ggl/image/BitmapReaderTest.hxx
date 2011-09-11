/*
 * BitmapReaderTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_BITMAPREADERTEST_HXX
#define GGL_BITMAPREADERTEST_HXX
#include "ggl/common.h"
#include <edo/TestFixture.hpp>
#include <edo/TestRunner.hpp>
#include "ggl/image/BitmapReader.hpp"
namespace Ggl {


/**
 * @brief Unit test for BitmapReader.
 */
class BitmapReaderTest : public Edo::TestFixture {
public:
    BitmapReaderTest();
    void testGetters();
    void testToImage();
private:
    BitmapReader reader;
};

} /* namespace Ggl */
#endif
