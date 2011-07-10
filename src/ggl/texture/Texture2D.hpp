/*
 * Texture2D.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TEXTURE2D_HPP
#define GGL_TEXTURE2D_HPP
#include "ggl/common.h"
#include "ggl/texture/Texture.hpp"
namespace Ggl {


/**
 * @brief Two-dimensional texture.
 */
class Texture2D : public Texture {
public:
    static Texture2D* newInstance(GLenum, GLsizei, GLsizei);
    virtual ~Texture2D();
// Getters
    GLsizei getDepth() const;
    GLuint getFormat() const;
    GLsizei getHeight() const;
    GLsizei getWidth() const;
private:
    GLenum format;
    GLsizei width;
    GLsizei height;
// Helpers
    void allocate();
    static bool isValidFormat(GLenum);
// Constructors
    Texture2D(GLenum, GLsizei, GLsizei);
};

} /* namespace Ggl */
#endif
