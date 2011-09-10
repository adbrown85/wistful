/*
 * Image.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_IMAGE_HPP
#define GGL_IMAGE_HPP
#include "ggl/common.h"
#include "ggl/Exception.hpp"
namespace Ggl {


/**
 * @brief Picture loaded into memory.
 * 
 * @ingroup image
 */
class Image {
public:
    Image(GLuint, GLenum, const GLubyte*, size_t, int, int);
    virtual ~Image();
// Getters
    virtual GLuint getAlignment() const;
    virtual GLenum getFormat() const;
    virtual int getHeight() const;
    virtual void getPixels(GLubyte *arr, size_t len) const;
    virtual size_t getSize() const;
    virtual int getWidth() const;
private:
    GLuint alignment;
    GLenum format;
    int height;
    size_t size;
    int width;
    GLubyte *pixels;
// Helpers
    static GLubyte* copyArray(const GLubyte *arr, size_t len);
// Constructors
    Image(const Image&);
    Image& operator=(const Image&);
};

} /* namespace Ggl */
#endif
