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
 * Utility for building shader programs.
 * 
 * @ingroup shader
 */
class ProgramBuilder {
public:
    ProgramBuilder();
    virtual ~ProgramBuilder();
    virtual void addShader(const std::string &filename);
    virtual void addShader(GLuint shader);
    virtual void bindAttribute(GLuint index, const std::string &name);
    virtual GLuint toProgram();
protected:
    static void report(GLuint handle);
private:
    std::list<GLuint> shaders;
    std::map<GLuint,std::string> locations;
// Constructors
    ProgramBuilder(const ProgramBuilder&);
    ProgramBuilder& operator=(const ProgramBuilder&);
};

} /* namespace Ggl */
#endif
