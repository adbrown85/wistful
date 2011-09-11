/*
 * Path.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/system/PathTest.hxx"
using namespace std;
using namespace Edo;
using namespace Ggl;

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
    assertEquals("input/glsl/file.frag", p1.toString());
    cout << p1.toString() << endl;
    
    Path p2 = locate("input/", "../glsl/file.frag");
    assertEquals("glsl/file.frag", p2.toString());
    cout << p2.toString() << endl;
    
    Path p3 = locate("input/", "../glsl/../glsl/file.frag");
    assertEquals("glsl/file.frag", p3.toString());
    cout << p3.toString() << endl;
    
    Path p4 = locate("../../input/", "file.frag");
    assertEquals("../../input/file.frag", p4.toString());
    cout << p4.toString() << endl;
}

void PathTest::testLocateWithAbsolute() {
    
    Path p1 = locate("input/", "/home/user/gander/glsl/file.frag");
    assertEquals("/home/user/gander/glsl/file.frag", p1.toString());
    cout << p1.toString() << endl;
    
    Path p2 = locate("/home/user/gander/input/", "glsl/file.frag");
    assertEquals("/home/user/gander/input/glsl/file.frag", p2.toString());
    cout << p2.toString() << endl;
    
    Path p3 = locate("/home/user/gander/input/", "../glsl/file.frag");
    assertEquals("/home/user/gander/glsl/file.frag", p3.toString());
    cout << p3.toString() << endl;
}

void PathTest::testDirname() {
    
    Path p1 = dirname("input/");
    assertEquals("input/", p1.toString());
    
    Path p2 = dirname("/");
    assertEquals("/", p2.toString());
    
    Path p3 = dirname("input/scene.xml");
    assertEquals("input/", p3.toString());
    
    Path p4 = dirname("scene.xml");
    assertEquals("", p4.toString());
}

void PathTest::testBasename() {
    
    Path p1 = basename("input/scene.xml");
    assertEquals("scene.xml", p1.toString());
    
    Path p2 = basename("README");
    assertEquals("README", p2.toString());
    
    Path p3 = basename("/");
    assertEquals("", p3.toString());
    
    Path p4 = basename("scene.xml");
    assertEquals("scene.xml", p4.toString());
}

Path PathTest::toPath(const string &str) {
    return Path::fromString(str);
}

Path PathTest::locate(const string &folder, const string &file) {
    return Path::locate(toPath(folder), toPath(file));
}

Path PathTest::dirname(const string &filename) {
    return Path::dirname(toPath(filename));
}

Path PathTest::basename(const string &filename) {
    return Path::basename(toPath(filename));
}

#define EDO_TEST_FIXTURE PathTest
EDO_TEST_SUITE
EDO_ADD_TEST(testToStringWithFile)
EDO_ADD_TEST(testToStringWithDirectory)
EDO_ADD_TEST(testToStringWithUnixRoot)
EDO_ADD_TEST(testToStringWithWindowsRoot)
EDO_ADD_TEST(testIsAbsoluteWithUnixRoot)
EDO_ADD_TEST(testIsAbsoluteWithWindowsRoot)
EDO_ADD_TEST(testIsDirectoryWithDirectory)
EDO_ADD_TEST(testIsDirectoryWithFile)
EDO_ADD_TEST(testLocateWithRelative)
EDO_ADD_TEST(testLocateWithAbsolute)
EDO_ADD_TEST(testDirname)
EDO_ADD_TEST(testBasename)
EDO_RUN_TESTS
