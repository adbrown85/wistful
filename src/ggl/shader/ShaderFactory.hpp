/*
 * ShaderFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_SHADERFACTORY_HPP
#define GGL_SHADERFACTORY_HPP
#include "ggl/common.h"
#include "ggl/shader/ShaderLoader.hpp"
namespace Ggl {


/**
 * @brief Utility for creating shaders.
 */
class ShaderFactory {
public:
    static GLuint create(const std::string &filename);
    static GLuint create(GLenum type, const std::string &filename);
private:
    static std::map<std::string,GLuint> shaders;
};

} /* namespace Ggl */
#endif
