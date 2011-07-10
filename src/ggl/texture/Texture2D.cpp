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
 * @throw std::exception if width is less than one
 * @throw std::exception if height is less than one
 */
void Texture2D::allocate(GLenum format, Dimension dimension) {
    
    GLuint width = dimension.getWidth();
    GLuint height = dimension.getHeight();
    
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
    
    // Store
    this->format = format;
    this->width = width;
    this->height = height;
}

//----------------------------------------
// Helpers
//

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
