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
 * Utility for creating shaders.
 *
 * @ingroup shader
 */
class ShaderFactory {
public:
    ShaderFactory();
    virtual ~ShaderFactory();
    GLuint create(const std::string &filename);
    GLuint create(const std::string &filename, GLenum type);
private:
    std::map<std::string,GLuint> shaders;
// Constructors
    ShaderFactory(const ShaderFactory&);
    ShaderFactory& operator=(const ShaderFactory&);
};

} /* namespace Ggl */
#endif
