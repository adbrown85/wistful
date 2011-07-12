/*
 * ShaderLoader.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_SHADERLOADER_HPP
#define GGL_SHADERLOADER_HPP
#include "ggl/common.h"
#include "ggl/Exception.hpp"
#include "ggl/shader/Preprocessor.hpp"
namespace Ggl {


/**
 * @brief Utility for creating, loading, and compiling shaders.
 */
class ShaderLoader {
public:
    static int load(const std::string &filename);
    static int load(GLenum type, const std::string &filename);
protected:
    static void compile(int handle);
    static int create(GLenum type);
    static std::string findExtension(const std::string &filename);
    static std::string findLog(GLuint handle);
    static GLenum findType(const std::string &filename);
    static void load(int handle, Code &code);
    static Code read(const std::string &filename);
};

} /* namespace Ggl */
#endif
