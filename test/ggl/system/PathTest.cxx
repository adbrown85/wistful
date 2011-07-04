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
private:
	static Path toPath(const string &str);
};

void PathTest::testToStringWithFile() {
    assertEquals("input/scene.xml", toPath("input/scene.xml").toString());
}

void PathTest::testToStringWithDirectory() {
    assertEquals("input/", toPath("input/").toString());
}

void PathTest::testToStringWithUnixRoot() {
    assertEquals("/", toPath("/").toString());
}

void PathTest::testToStringWithWindowsRoot() {
    assertEquals("C:/", toPath("C:\\").toString());
}

void PathTest::testIsAbsoluteWithUnixRoot() {
    assert(toPath("/").isAbsolute());
}

void PathTest::testIsAbsoluteWithWindowsRoot() {
    assert(toPath("C:\\").isAbsolute());
}

void PathTest::testIsDirectoryWithDirectory() {
    assert(toPath("input/scenes/").isDirectory());
}

void PathTest::testIsDirectoryWithFile() {
    assert(!toPath("input/scene.xml").isDirectory());
}

Path PathTest::toPath(const string &str) {
    return Path::fromString(str);
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
