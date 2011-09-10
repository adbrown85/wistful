/*
 * ShaderLoader.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_SHADERLOADER_HPP
#define GGL_SHADERLOADER_HPP
#include <fstream>
#include <iomanip>
#include <set>
#include "ggl/common.h"
#include "ggl/Exception.hpp"
#include "ggl/shader/ShaderBuilder.hpp"
#include "ggl/system/Path.hpp"
namespace Ggl {


/**
 * Utility for creating, loading, and compiling shaders.
 *
 * @ingroup shader
 */
class ShaderLoader {
public:
    static GLuint load(const std::string &filename);
    static GLuint load(const std::string &filename, GLenum type);
private:
// Nested classes
    class Line;
    class Code;
    class Preprocessor;
// Helpers
    static std::string findExtension(const std::string &filename);
    static GLenum findType(const std::string &filename);
    static Code read(const std::string &filename);
// Constructors
    ShaderLoader();
    ShaderLoader(const ShaderLoader&);
    ShaderLoader& operator=(const ShaderLoader&);
};


/**
 * Line of code.
 */
struct ShaderLoader::Line {
    std::string filename;
    std::string text;
    int number;
};


/**
 * Source code loaded from multiple files.
 */
class ShaderLoader::Code {
public:
    typedef std::vector<Line>::iterator iterator;
public:
    void addLine(const std::string &f, int n, const std::string &t);
    void clearLines();
// Accessors
    iterator begin();
    iterator end();
    Line getLine(int number) const;
    size_t size() const;
private:
    std::vector<Line> lines;
};


/**
 * Utility for preprocessing C-like code.
 * 
 * Basically, %Preprocessor simply looks through C-like code and
 * performs a few simple operations.  First, if it finds an @e include
 * directive, it replaces that line with the lines from the appropriate
 * file.  Lastly, it strips both multiline and single line comments, as
 * well as trailing spaces.
 */
class ShaderLoader::Preprocessor {
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
