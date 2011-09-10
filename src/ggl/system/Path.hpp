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
 *
 * @ingroup system
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
    static Path basename(const Path &path);
    static Path dirname(const Path &path);
    static Path locate(const Path &folder, const Path &file);
private:
    std::string root;
    stringlist_t parts;
    bool directory;
/* Helpers */
    static stringlist_t createParts(const std::string &filename);
    static std::string createRoot(const std::string &filename);
    static bool endsWithSeparator(const std::string &str);
    static bool hasUnixRoot(const std::string &str);
    static bool hasWindowsRoot(const std::string &str);
    static bool isSeparator(char c);
    static bool isWindowsRoot(const std::string &str);
    static stringlist_t tokenize(const std::string &filename);
/* Constructors */
    Path(const std::string&, const stringlist_t&, bool);
};

} /* namespace Ggl */
#endif
