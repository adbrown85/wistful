/*
 * Path.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PATH_HPP
#define GGL_PATH_HPP
#include <cctype>
#include <sstream>
#include "ggl/common.h"
#include "ggl/Exception.hpp"
#include "ggl/system/Text.hpp"
namespace Ggl {


/**
 * @brief Location of a file.
 */
class Path {
public:
    static Path fromString(const std::string &str);
    virtual ~Path();
    virtual bool isAbsolute() const;
    virtual bool isDirectory() const;
    virtual std::string toString() const;
private:
    std::list<std::string> parts;
    std::string root;
/* Helpers */
    static std::list<std::string> createParts(const std::string &filename);
    static std::string createRoot(const std::string &filename);
    static bool hasUnixRoot(const std::string &str);
    static bool hasWindowsRoot(const std::string &str);
    static bool isSeparator(char c);
    static bool isWindowsRoot(const std::string &str);
    static std::list<std::string> tokenize(const std::string &filename);
/* Constructors */
    Path(const std::string &root, const std::list<std::string> &parts);
};

} /* namespace Ggl */
#endif
