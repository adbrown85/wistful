/*
 * Texture.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TEXTURE_HPP
#define GGL_TEXTURE_HPP
#include "ggl/common.h"
#include "ggl/Exception.hpp"
namespace Ggl {


/**
 * @brief OpenGL texture.
 */
class Texture {
public:
    Texture(GLuint handle);
    virtual ~Texture();
// Getters
    GLuint getHandle() const;
private:
    GLuint handle;
// Helpers
    static bool isTexture(GLuint handle);
};

} /* namespace Ggl */
#endif
