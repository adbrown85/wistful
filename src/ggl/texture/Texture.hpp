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
#include "ggl/system/Dimension.hpp"
namespace Ggl {


/**
 * @brief Base class for an OpenGL texture.
 */
class Texture {
public:
    explicit Texture(GLenum target);
    virtual ~Texture();
    virtual void bind() const;
    virtual void allocate(GLenum format, Dimension dimension) = 0;
    virtual void load(GLenum format, GLenum type, const GLubyte *data) = 0;
// Getters
    virtual GLsizei getDepth() const = 0;
    virtual GLenum getFormat() const = 0;
    virtual GLuint getHandle() const;
    virtual GLsizei getHeight() const = 0;
    virtual GLenum getTarget() const;
    virtual GLsizei getWidth() const = 0;
protected:
    static bool isValidFormat(GLenum format);
    static bool isValidTarget(GLenum target);
private:
    GLuint handle;
    GLenum target;
// Helpers
    static GLuint createHandle();
// Constructors
    Texture(const Texture&);
    Texture& operator=(const Texture&);
};

} /* namespace Ggl */
#endif
