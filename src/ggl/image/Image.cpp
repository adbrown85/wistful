/*
 * Image.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/image/Image.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates an image.
 * 
 * @param alignment Number of bytes row length should be multiples of
 * @param format Type and number of pixels, e.g. GL_RGB or GL_RGBA
 * @param pixels Pointer to an array of color values
 * @param size Total number of bytes required to hold pixel data
 * @param width Size of image in X direction
 * @param height Size of image in Y direction
 */
Image::Image(GLuint alignment,
             GLenum format,
             const GLubyte *pixels,
             size_t size,
             int width,
             int height) {
    this->width = width;
    this->height = height;
    this->format = format;
    this->pixels = copyArray(pixels, size);
    this->size = size;
    this->alignment = alignment;
}

/**
 * Destroys the image.
 */
Image::~Image() {
    if (pixels != NULL) {
        delete[] pixels;
    }
}

// HELPERS

/**
 * Creates a copy of an array.
 * 
 * @param arr Array to copy
 * @param len Length of array
 * @return Pointer to new array
 */
GLubyte* Image::copyArray(const GLubyte *arr, size_t len) {
    
    GLubyte *copy = new GLubyte[len];
    
    // Check allocation
    if (copy == NULL) {
        throw Exception("[Image] Could not allocate enough memory!");
    }
    
    // Copy to new array
    memcpy(copy, arr, len);
    return copy;
}

// GETTERS

/**
 * Returns number of bytes that row length should be multiples of.
 */
GLuint Image::getAlignment() const {
    return alignment;
}

/**
 * Returns GL_RGB or GL_RGBA.
 */
GLenum Image::getFormat() const {
    return format;
}

/**
 * Returns size of the image in the Y direction.
 */
int Image::getHeight() const {
    return height;
}

/**
 * Copies the image's pixels to another array.
 * 
 * @param arr Array to copy to
 * @param len Length of array
 * @throw std::exception if array is not correct length
 */
void Image::getPixels(GLubyte *arr, size_t len) const {
    if (len != getSize()) {
       throw Exception("[Image] Array is not correct size!");
    } else {
        memcpy(arr, pixels, len);
    }
}

/**
 * Returns total number of bytes required to hold the pixel data.
 */
size_t Image::getSize() const {
    return size;
}

/**
 * Returns size of the image in the X direction.
 */
int Image::getWidth() const {
    return width;
}
