/*
 * BitmapReader.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "ggl/image/BitmapReaderTest.hxx"
using namespace std;
using namespace Edo;
using namespace Ggl;

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
#define EDO_TEST_FIXTURE BitmapReaderTest
EDO_TEST_SUITE
EDO_ADD_TEST(testGetters)
EDO_ADD_TEST(testToImage)
EDO_RUN_TESTS

