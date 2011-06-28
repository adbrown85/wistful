/*
 * TestFixture.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/testing/TestFixture.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates an empty test case.
 */
TestFixture::TestFixture() {
    ;
}

/**
 * Destroys the test case.
 */
TestFixture::~TestFixture() {
    ;
}

/**
 * Prepares the test fixture for a test case.
 */
void TestFixture::setUp() {
    ;
}

/**
 * Cleans up the test fixture after a test case.
 */
void TestFixture::tearDown() {
    ;
}

//----------------------------------------
// Helpers
//

/**
 * Checks to see if two values are approximately equal.
 * 
 * @param x First value
 * @param y Second value
 */
void TestFixture::assertEquals(float x, float y) {
    assertEquals(x, y, DEFAULT_EPSILON);
}

/**
 * Checks to see if two values are approximately equal.
 * 
 * @param x First value
 * @param y Second value
 * @param epsilon Margin of error
 */
void TestFixture::assertEquals(float x, float y, float epsilon) {
    if (fabs(x - y) > epsilon) {
        throw Exception(createMessage(x, y));
    }
}

/**
 * Makes a message for an exception.
 * 
 * @param x Expected value
 * @param y Actual value
 * @return Message listing both values
 */
string TestFixture::createMessage(float x, float y) {
    
    stringstream ss;
    
    ss << "Expected [" << x << "] but was [" << y << "]!";
    return ss.str();
}
