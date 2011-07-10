/*
 * PathTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PATHTEST_HXX
#define GGL_PATHTEST_HXX
#define GGL_TEST_FIXTURE PathTest
#include "ggl/system/Path.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestSuite.hpp"
#include "ggl/testing/TestRunner.hpp"
namespace Ggl {


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
    void testDirname();
    void testBasename();
private:
    static Path toPath(const std::string &str);
    static Path locate(const std::string &folder, const std::string &file);
    static Path dirname(const std::string &path);
    static Path basename(const std::string &path);
};

} /* namespace Ggl */
#endif
