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
 * @throw std::exception if handle is not a texture
 */
Texture::Texture(GLuint handle) {
    if (handle == 0) {
        throw Exception("[Texture] Handle is zero!");
    } else if (!isTexture(handle)) {
        throw Exception("[Texture] Handle is not a texture!");
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

//----------------------------------------
// Helpers
//

/**
 * Determines if a handle is a texture.
 * 
 * @param handle Identifier for an OpenGL object
 * @return <tt>true</tt> if the handle is a texture
 */
bool Texture::isTexture(GLuint handle) {
    return glIsTexture(handle);
}
