/*
 * ProgramBuilder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PROGRAMBUILDER_HPP
#define GGL_PROGRAMBUILDER_HPP
#include "ggl/common.h"
namespace Ggl {


/**
 * @brief Utility for building shader programs.
 */
class ProgramBuilder {
public:
	static GLuint build(GLuint vertexShader, GLuint fragmentShader);
	static GLuint build(std::list<GLuint> &shaders);
protected:
	static void report(GLuint handle);
};

} /* namespace Ggl */
#endif
