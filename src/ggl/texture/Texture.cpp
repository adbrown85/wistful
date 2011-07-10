/*
 * Texture.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/texture/Texture.hpp"
using namespace std;
using namespace Ggl;

/**
 * Constructs a new texture.
 * 
 * @param target Kind of texture, e.g. GL_TEXTURE_2D
 * @throw std::exception if target invalid
 */
Texture::Texture(GLenum target) {
    if (!isValidTarget(target)) {
        throw Exception("[Texture] Target is invalid!");
    } else {
        this->target = target;
        this->handle = createHandle();
    }
}

/**
 * Copies another texture.
 * 
 * @param texture Texture to copy
 * @throw Exception if called
 */
Texture::Texture(const Texture &texture) {
    throw Exception("[Texture] Cannot copy texture!");
}

/**
 * Destroys the texture.
 */
Texture::~Texture() {
    glDeleteTextures(1, &handle);
}

/**
 * Binds the texture to the current texture unit.
 */
void Texture::bind() const {
    glBindTexture(target, handle);
}

//----------------------------------------
// Getters
//

/**
 * Returns internal OpenGL identifier for texture.
 */
GLuint Texture::getHandle() const {
    return handle;
}

/**
 * Returns kind of texture.
 */
GLenum Texture::getTarget() const {
    return target;
}

//----------------------------------------
// Helpers
//

/**
 * Returns the handle to a new OpenGL texture object.
 */
GLuint Texture::createHandle() {
    
    GLuint handle;
    
    glGenTextures(1, &handle);
    return handle;
}

/**
 * Checks if a value is a valid texture format.
 * 
 * @param value Value to check
 * @return <tt>true</tt> if value is a valid texture format
 */
bool Texture::isValidFormat(GLenum value) {
    switch (value) {
    case GL_RGB:
    case GL_RGBA:
        return true;
    default:
        return false;
    }
}

/**
 * Checks if a value is a valid texture target.
 * 
 * @param value Value to check
 * @return <tt>true</tt> if value is valid
 */
bool Texture::isValidTarget(GLenum value) {
    switch (value) {
    case GL_TEXTURE_1D:
    case GL_TEXTURE_2D:
    case GL_TEXTURE_3D:
        return true;
    default:
        return false;
    }
}
