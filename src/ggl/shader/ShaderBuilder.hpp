/*
 * ShaderBuilder.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_SHADERBUILDER_HPP
#define GGL_SHADERBUILDER_HPP
#include <vector>
#include "ggl/common.h"
#include "ggl/Exception.hpp"
namespace Ggl {


/**
 * @brief Utility for creating shaders.
 */
class ShaderBuilder {
public:
    ShaderBuilder();
    virtual ~ShaderBuilder();
    virtual void addLine(const std::string &line);
    virtual void addLines(const std::list<std::string> &lines);
    virtual void addLines(const std::vector<std::string> &lines);
    virtual GLuint toShader(GLenum type);
private:
    std::vector<std::string> lines;
// Helpers
    static void compile(GLuint handle);
    static GLuint create(GLenum type);
    static std::string getLog(GLuint handle);
    static void load(GLuint handle, const std::vector<std::string> &lines);
// Constructors
    ShaderBuilder(const ShaderBuilder&);
    ShaderBuilder& operator=(const ShaderBuilder&);
};

} /* namespace Ggl */
#endif
