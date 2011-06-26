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
 * Checks to see if two values are equal.
 * 
 * @param x First value
 * @param y Second value
 */
void TestFixture::assertEquals(float x, float y) {
    assert(fabs(x - y) < EPSILON);
}
