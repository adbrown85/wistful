/*
 * Path.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/system/Path.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestSuite.hpp"
#include "ggl/testing/TestRunner.hpp"
using namespace std;
using namespace Ggl;

/**
 * @brief Unit test for Path.
 */
class PathTest : public TestFixture {
public:
    void testToStringWithFile();
    void testToStringWithDirectory();
    void testToStringWithUnixRoot();
    void testToStringWithWindowsRoot();
	void testIsAbsoluteWithUnixRoot();
	void testIsAbsoluteWithWindowsRoot();
	void testIsDirectoryWithDirectory();
	void testIsDirectoryWithFile();
};

void PathTest::testToStringWithFile() {
    assertEquals("input/scene.xml", Path("input/scene.xml").toString());
}

void PathTest::testToStringWithDirectory() {
    assertEquals("input/", Path("input/").toString());
}

void PathTest::testToStringWithUnixRoot() {
    assertEquals("/", Path("/").toString());
}

void PathTest::testToStringWithWindowsRoot() {
    assertEquals("C:/", Path("C:\\").toString());
}

void PathTest::testIsAbsoluteWithUnixRoot() {
    assert(Path("/").isAbsolute());
}

void PathTest::testIsAbsoluteWithWindowsRoot() {
    assert(Path("C:\\").isAbsolute());
}

void PathTest::testIsDirectoryWithDirectory() {
    assert(Path("input/scenes/").isDirectory());
}

void PathTest::testIsDirectoryWithFile() {
    assert(!Path("input/scene.xml").isDirectory());
}

#define GGL_TEST_FIXTURE PathTest
GGL_TEST_SUITE
GGL_ADD_TEST(testToStringWithFile)
GGL_ADD_TEST(testToStringWithDirectory)
GGL_ADD_TEST(testToStringWithUnixRoot)
GGL_ADD_TEST(testToStringWithWindowsRoot)
GGL_ADD_TEST(testIsAbsoluteWithUnixRoot)
GGL_ADD_TEST(testIsAbsoluteWithWindowsRoot)
GGL_ADD_TEST(testIsDirectoryWithDirectory)
GGL_ADD_TEST(testIsDirectoryWithFile)
GGL_RUN_TESTS
