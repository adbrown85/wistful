/*
 * TextTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TEXTTEST_HXX
#define GGL_TEXTTEST_HXX
#include <edo/TestFixture.hpp>
#include <edo/TestRunner.hpp>
#include "ggl/system/Text.hpp"
namespace Ggl {


/**
 * Unit test for Text.
 */
class TextTest : public Edo::TestFixture {
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
