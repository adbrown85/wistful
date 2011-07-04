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
    typedef std::list<std::string> stringlist_t;
public:
    static Path fromString(const std::string &str);
    virtual ~Path();
    virtual bool isAbsolute() const;
    virtual bool isDirectory() const;
    virtual std::string toString() const;
/* Utilities */
    static Path locate(const Path &folder, const Path &file);
private:
    stringlist_t parts;
    std::string root;
/* Helpers */
    static stringlist_t createParts(const std::string &filename);
    static std::string createRoot(const std::string &filename);
    static bool hasUnixRoot(const std::string &str);
    static bool hasWindowsRoot(const std::string &str);
    static bool isSeparator(char c);
    static bool isWindowsRoot(const std::string &str);
    static stringlist_t tokenize(const std::string &filename);
/* Constructors */
    Path(const std::string &root, const stringlist_t &parts);
};

} /* namespace Ggl */
#endif
