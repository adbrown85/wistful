/*
 * TextTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/system/Text.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
using namespace std;
using namespace Ggl;

/**
 * Test for Text.
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

void TextTest::testCount() {
    
    int result;
    
    result = Text::count("abracadabra", 'a');
    assert(result == 5);
}

void TextTest::testFirstWordCharacter() {
    
    int result;
    
    result = Text::findFirstWordCharacter("    (foo)", 0);
    assert(result == 5);
}

void TextTest::testFirstNotWordCharacter() {
    
    int result;
    
    result = Text::findFirstNotWordCharacter("    (foo)", 5);
    assert(result == 8);
}

void TextTest::testFirstWord() {
    
    pair<int,int> result;
    string text;
    
    text = "    (foo)";
    result = Text::findFirstWord(text);
    assert(result.first  == 5);
    assert(result.second == 3);
    assert(text.substr(result.first,result.second) == "foo");
    
    text = " 78 * 45";
    result = Text::findFirstWord(text);
    assert(result.first  == -1);
    assert(result.second == 0);
    
    text = " 123foobar";
    result = Text::findFirstWord(text);
    assert(result.first  == 4);
    assert(result.second == 6);
    assert(text.substr(result.first,result.second) == "foobar");
}

void TextTest::testReplacements() {
    
    map<string,string> dictionary;
    string result;
    
    dictionary["PI_CONSTANT"] = "3.14";
    dictionary["E_CONSTANT"] = "2.72";
    result = Text::replace("4*PI_CONSTANT + E_CONSTANT BLAH", dictionary);
    assert(result == "4*3.14 + 2.72 BLAH");
}

void TextTest::testTrim() {
    
    string result;
    
    result = Text::trim("  blah blah blah  ");
    assert(result == "blah blah blah");
    
    result = Text::trim("  \"blah blah blah\"  ", "'\" ");
    assert(result == "blah blah blah");
}

void TextTest::testSplit() {
    
    pair<string,string> result;
    
    result = Text::split("spot.ambient", '.');
    assert(result.first == "spot");
    assert(result.second == "ambient");
}

void TextTest::testStripLeadingSpaces() {
    
    string result;
    
    result = Text::stripLeadingSpaces("\t // This is a comment");
    assert(result == "// This is a comment");
}

void TextTest::testStripTrailingSpaces() {
    
    string result;
    
    result = Text::stripTrailingSpaces("// This is a comment    ");
    assert(result == "// This is a comment");
}

#define GGL_TEST_FIXTURE TextTest
GGL_TEST_SUITE
GGL_ADD_TEST(testCount)
GGL_ADD_TEST(testFirstWordCharacter)
GGL_ADD_TEST(testFirstNotWordCharacter)
GGL_ADD_TEST(testFirstWord)
GGL_ADD_TEST(testReplacements)
GGL_ADD_TEST(testTrim)
GGL_ADD_TEST(testSplit)
GGL_ADD_TEST(testStripLeadingSpaces)
GGL_ADD_TEST(testStripTrailingSpaces)
GGL_RUN_TESTS

