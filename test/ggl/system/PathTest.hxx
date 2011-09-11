/*
 * PathTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PATHTEST_HXX
#define GGL_PATHTEST_HXX
#include <edo/TestFixture.hpp>
#include <edo/TestSuite.hpp>
#include <edo/TestRunner.hpp>
#include "ggl/system/Path.hpp"
namespace Ggl {


/**
 * @brief Unit test for Path.
 */
class PathTest : public Edo::TestFixture {
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
