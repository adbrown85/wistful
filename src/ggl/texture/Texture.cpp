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
 * Creates a texture.
 * 
 * @param handle OpenGL identifier for a texture
 * @throw std::exception if handle is zero
 */
Texture::Texture(GLuint handle) {
    if (handle == 0) {
        throw Exception("[Texture] Handle is zero!");
    } else {
        this->handle = handle;
    }
}

/**
 * Destroys the texture.
 */
Texture::~Texture() {
    ;
}

/**
 * Returns the OpenGL identifier.
 */
GLuint Texture::getHandle() const {
    return handle;
}
