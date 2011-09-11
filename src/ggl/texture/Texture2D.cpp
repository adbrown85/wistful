/*
 * Texture2D.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/texture/Texture2D.hpp"
using namespace std;
using namespace Edo;
using namespace Ggl;

/**
 * Creates a new two-dimensional texture.
 */
Texture2D* Texture2D::newInstance() {
    return new Texture2D();
}

/**
 * Constructs a two-dimensional texture.
 */
Texture2D::Texture2D() : Texture(GL_TEXTURE_2D) {
    this->format = 0;
    this->width = 0;
    this->height = 0;
}

/**
 * Destroys the texture.
 */
Texture2D::~Texture2D() {
    ;
}

/**
 * Reserves memory for the texture.
 * 
 * @param format Internal format of texture, e.g. GL_RGB
 * @param dimension Width and height of texture
 * @throw std::exception if dimension is invalid
 */
void Texture2D::allocate(GLenum format, Dimension dimension) {
    
    GLsizei width = dimension.getWidth();
    GLsizei height = dimension.getHeight();
    
    allocate(format, width, height);
}

/**
 * Reserves memory for the texture.
 * 
 * @param format Internal format of texture, e.g. GL_RGB
 * @param width Size of texture on X axis
 * @param height Size of texture on Y axis
 * @throw std::exception if width is less than one
 * @throw std::exception if height is less than one
 */
void Texture2D::allocate(GLenum format, GLsizei width, GLsizei height) {
    
    // Validate
    if (!isValidFormat(format)) {
        throw Exception("[Texture2D] Format is invalid!");
    } else if (width < 1) {
        throw Exception("[Texture2D] Width is less than one!");
    } else if (height < 1) {
        throw Exception("[Texture2D] Height is less than one!");
    }
    
    // Allocate
    glTexImage2D(
            GL_TEXTURE_2D,     // target
            0,                 // level
            format,            // internal format
            width,             // width
            height,            // height
            0,                 // border
            GL_RGB,            // data format
            GL_UNSIGNED_BYTE,  // data type
            NULL);             // data
    
    // Set filtering
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Store
    this->format = format;
    this->width = width;
    this->height = height;
}

/**
 * Copies data from an image into the texture.
 * 
 * @param image Image to copy
 * @throw std::exception if width does not match texture
 * @throw std::exception if height does not match texture
 */
void Texture2D::load(const Image &image) {
    
    const GLenum format = image.getFormat();
    const GLuint width = image.getWidth();
    const GLuint height = image.getHeight();
    const GLuint len = image.getSize();
    GLubyte *pixels;
    
    if (width != getWidth()) {
        throw Exception("[Texture2D] Width does not match!");
    } else if (height != getHeight()) {
        throw Exception("[Texture2D] Height does not match!");
    }
    
    pixels = new GLubyte[len];
    try {
        image.getPixels(pixels, len);
        load(format, GL_UNSIGNED_BYTE, pixels);
    } catch (exception &e) {
        delete[] pixels;
        throw Exception(e.what());
    }
    
    delete[] pixels;
}

/**
 * Copies data into the texture.
 * 
 * @param format Format of data, e.g. GL_RGB
 * @param type Primitive type of data, e.g. GL_UNSIGNED_BYTE
 * @param data Pointer to data to load
 */
void Texture2D::load(GLenum format, GLenum type, const GLubyte *data) {
    glTexSubImage2D(
            GL_TEXTURE_2D,     // target
            0,                 // level
            0,                 // x offset
            0,                 // y offset
            width,             // width
            height,            // height
            format,            // format
            type,              // type
            data);             // data
}

//----------------------------------------
// Getters
//

GLsizei Texture2D::getDepth() const {
    return 1;
}

GLenum Texture2D::getFormat() const {
    return format;
}

GLsizei Texture2D::getHeight() const {
    return height;
}

GLsizei Texture2D::getWidth() const {
    return width;
}
