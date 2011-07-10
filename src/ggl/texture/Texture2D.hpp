/*
 * Texture2D.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TEXTURE2D_HPP
#define GGL_TEXTURE2D_HPP
#include "ggl/common.h"
#include "ggl/image/Image.hpp"
#include "ggl/system/Dimension.hpp"
#include "ggl/texture/Texture.hpp"
namespace Ggl {


/**
 * @brief Two-dimensional texture.
 */
class Texture2D : public Texture {
public:
    static Texture2D* newInstance();
    virtual ~Texture2D();
    virtual void allocate(GLenum format, Dimension dimension);
    virtual void load(const Image &image);
    virtual void load(GLenum format, GLenum type, const GLubyte *data);
// Getters
    GLsizei getDepth() const;
    GLuint getFormat() const;
    GLsizei getHeight() const;
    GLsizei getWidth() const;
private:
    GLenum format;
    GLsizei width;
    GLsizei height;
// Constructors
    Texture2D();
};

} /* namespace Ggl */
#endif
