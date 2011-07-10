/*
 * TextTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TEXTTEST_HXX
#define GGL_TEXTTEST_HXX
#define GGL_TEST_FIXTURE TextTest
#include "ggl/system/Text.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
namespace Ggl {


/**
 * Unit test for Text.
 */
class TextTest : public TestFixture {
public:
    void testCount();
    void testFirstWord();
    void testFirstWordCharacter();
    void testFirstNotWordCharacter();
    void testReplacements();
    void testTrim();
    void testStripLeadingSpaces();
    void testStripTrailingSpaces();
    void testSplit();
};

} /* namespace Ggl */
#endif
