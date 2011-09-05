/*
 * Preprocessor.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PREPROCESSOR_HPP
#define GGL_PREPROCESSOR_HPP
#include "ggl/common.h"
#include <fstream>
#include <iomanip>
#include <set>
#include "ggl/shader/Code.hpp"
#include "ggl/system/Path.hpp"
namespace Ggl {


/**
 * @brief Utility for preprocessing C-like code.
 * 
 * Basically, %Preprocessor simply looks through C-like code and
 * performs a few simple operations.  First, if it finds an @e include
 * directive, it replaces that line with the lines from the appropriate
 * file.  Lastly, it strips both multiline and single line comments, as
 * well as trailing spaces.
 */
class Preprocessor {
public:
    Preprocessor();
    void parse(const std::string &filename);
    Code getCode() const;
private:
    std::set<std::string> includes;
    std::string filename;
    Code code;
// Helpers
    static std::string after(const std::string &str, char c);
    static std::string trim(const std::string &str, const std::string &c);
    bool isInclude(const std::string &line);
    void load(const std::string &filename);
    void onInclude(const std::string &line);
    void onLine(const std::string &f, int n, std::string &t, bool& ic);
    std::string stripComments(const std::string &line, bool &inComment);
// Constructors
    Preprocessor(const Preprocessor&);
    Preprocessor& operator=(const Preprocessor&);
};

} /* namespace Ggl */
#endif
