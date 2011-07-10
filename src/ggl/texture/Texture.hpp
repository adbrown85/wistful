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
 * @brief Base class for an OpenGL texture.
 */
class Texture {
public:
    Texture(GLenum target);
    virtual ~Texture();
    virtual void bind() const;
// Getters
    virtual GLsizei getDepth() const = 0;
    virtual GLenum getFormat() const = 0;
    virtual GLuint getHandle() const;
    virtual GLsizei getHeight() const = 0;
    virtual GLenum getTarget() const;
    virtual GLsizei getWidth() const = 0;
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
