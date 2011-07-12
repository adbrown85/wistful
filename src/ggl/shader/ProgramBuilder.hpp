/*
 * ProgramBuilder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PROGRAMBUILDER_HPP
#define GGL_PROGRAMBUILDER_HPP
#include "ggl/common.h"
#include "ggl/shader/ShaderLoader.hpp"
namespace Ggl {


/**
 * @brief Utility for building shader programs.
 */
class ProgramBuilder {
public:
    ProgramBuilder();
    virtual ~ProgramBuilder();
    virtual void addShader(const std::string &filename);
    virtual void addShader(GLuint shader);
    virtual GLuint toProgram();
protected:
    static void report(GLuint handle);
private:
    std::list<GLuint> shaders;
};

} /* namespace Ggl */
#endif
