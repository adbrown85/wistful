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
    Texture(GLenum target);
    virtual ~Texture();
    virtual void bind() const;
// Getters
    virtual GLuint getHandle() const;
    virtual GLenum getTarget() const;
private:
    GLuint handle;
    GLenum target;
// Helpers
    static GLuint createHandle();
    static bool isValidTarget(GLenum target);
// Constructors
    Texture(const Texture&);
};

} /* namespace Ggl */
#endif
