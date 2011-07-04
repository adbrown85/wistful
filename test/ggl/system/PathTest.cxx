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
	void testLocateWithRelative();
	void testLocateWithAbsolute();
private:
	static Path toPath(const string &str);
	static Path locate(const string &folder, const string &file);
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

void PathTest::testLocateWithRelative() {
    
    Path p1 = locate("input/", "glsl/file.frag");
    assertEquals("input//glsl/file.frag", p1.toString());
    cout << p1.toString() << endl;
    
    Path p2 = locate("input/", "../glsl/file.frag");
    assertEquals("glsl/file.frag", p2.toString());
    cout << p2.toString() << endl;
    
    Path p3 = locate("input/", "../glsl/../glsl/file.frag");
    assertEquals("glsl/file.frag", p3.toString());
    cout << p3.toString() << endl;
    
    Path p4 = locate("../../input/", "file.frag");
    assertEquals("../../input//file.frag", p4.toString());
    cout << p4.toString() << endl;
}

void PathTest::testLocateWithAbsolute() {
    
    Path p1 = locate("input/", "/home/user/gander/glsl/file.frag");
    assertEquals("/home/user/gander/glsl/file.frag", p1.toString());
    cout << p1.toString() << endl;
    
    Path p2 = locate("/home/user/gander/input/", "glsl/file.frag");
    assertEquals("/home/user/gander/input//glsl/file.frag", p2.toString());
    cout << p2.toString() << endl;
    
    Path p3 = locate("/home/user/gander/input/", "../glsl/file.frag");
    assertEquals("/home/user/gander/glsl/file.frag", p3.toString());
    cout << p3.toString() << endl;
}

Path PathTest::toPath(const string &str) {
    return Path::fromString(str);
}

Path PathTest::locate(const string &folder, const string &file) {
    return Path::locate(toPath(folder), toPath(file));
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
GGL_ADD_TEST(testLocateWithRelative)
GGL_ADD_TEST(testLocateWithAbsolute)
GGL_RUN_TESTS
