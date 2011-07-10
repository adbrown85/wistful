/*
 * Texture2D.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/texture/Texture2D.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates, binds, and allocates a new two-dimensional texture.
 * 
 * @param format Internal format of texture, e.g. GL_RGB
 * @param width Size of texture on X axis
 * @param height Size of texture on Y axis
 * @throw std::exception if width is less than one
 * @throw std::exception if height is less than one
 */
Texture2D* Texture2D::newInstance(GLenum format,
                                  GLsizei width,
                                  GLsizei height) {
    
    Texture2D *texture;
    
    // Validate
    if (!isValidFormat(format)) {
        throw Exception("[Texture2D] Format is invalid!");
    } else if (width < 1) {
        throw Exception("[Texture2D] Width is less than one!");
    } else if (height < 1) {
        throw Exception("[Texture2D] Height is less than one!");
    }
    
    // Generate and allocate
    texture = new Texture2D(format, width, height);
    texture->bind();
    texture->allocate();
    return new Texture2D(format, width, height);
}

/**
 * Constructs a two-dimensional texture.
 * 
 * @param format Internal format of texture, e.g. GL_RGB
 * @param width Size of texture on X axis
 * @param height Size of texture on Y axis
 */
Texture2D::Texture2D(GLenum format,
                     GLsizei width,
                     GLsizei height) : Texture(GL_TEXTURE_2D) {
    this->format = format;
    this->width = width;
    this->height = height;
}

/**
 * Destroys the texture.
 */
Texture2D::~Texture2D() {
    ;
}

//----------------------------------------
// Helpers
//

/**
 * Reserves memory for the texture.
 */
void Texture2D::allocate() {
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
}

/**
 * Checks if a value if a valid texture format.
 * 
 * @param value Value to check
 * @return <tt>true</tt> if value is a valid texture format
 */
bool Texture2D::isValidFormat(GLenum value) {
    switch (value) {
    case GL_RGB:
    case GL_RGBA:
        return true;
    default:
        return false;
    }
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
