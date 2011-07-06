/*
 * BitmapReader.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/common.h"
#include "ggl/image/BitmapReader.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
using namespace std;
using namespace Ggl;


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

/** Read the image into memory. */
BitmapReaderTest::BitmapReaderTest() {
    reader.read("test/ggl/image/rgbw.bmp");
}

/** Ensures the file can be loaded. */
void BitmapReaderTest::testGetters() {
    assert(reader.getWidth() == 2);
    assert(reader.getHeight() == 2);
    assert(reader.getFormat() == GL_BGR);
    assert(reader.getSize() == 16);
}

/** Ensures pixel data is correct. */
void BitmapReaderTest::testToImage() {
    
    GLubyte arr[16];
    Image *image = reader.toImage();
    
    assert(image->getSize() == 16);
    image->getPixels((GLubyte*) arr, 16);
    
    // Bottom row (red and white)
    assert(arr[ 0] ==   0); // B
    assert(arr[ 1] ==   0); // G
    assert(arr[ 2] == 255); // R
    assert(arr[ 3] == 255); // B
    assert(arr[ 4] == 255); // G
    assert(arr[ 5] == 255); // R
    
    // Top row (blue and green)
    assert(arr[ 8] == 255); // B
    assert(arr[ 9] ==   0); // G
    assert(arr[10] ==   0); // R
    assert(arr[11] ==   0); // B
    assert(arr[12] == 255); // G
    assert(arr[13] ==   0); // R
}

/* Run the test. */
#define GGL_TEST_FIXTURE BitmapReaderTest
GGL_TEST_SUITE
GGL_ADD_TEST(testGetters)
GGL_ADD_TEST(testToImage)
GGL_RUN_TESTS

