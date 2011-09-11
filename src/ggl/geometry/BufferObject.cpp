/*
 * BufferObject.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "ggl/geometry/BufferObject.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates a new buffer object.
 */
BufferObject::BufferObject(GLenum type) {
    this->type = type;
    this->handle = createHandle();
}

/**
 * Destroys the buffer object.
 */
BufferObject::~BufferObject() {
    glDeleteBuffers(1, &handle);
}

/**
 * Activates the buffer object.
 */
void BufferObject::bind() {
    glBindBuffer(type, handle);
}

/**
 * Stops using the buffer object.
 */
void BufferObject::unbind() {
    glBindBuffer(type, 0);
}

/**
 * Allocates enough room for the VBO.
 */
void BufferObject::allocate(GLenum usage, GLsizei size) {
    glBufferData(
            type,                // target
            size,                // size
            NULL,                // data
            usage);              // usage
}

/**
 * Fills the buffer with data.
 */
void BufferObject::update(GLsizei size, GLvoid *data, int offset) {
    glBufferSubData(
            type,             // target
            offset,           // offset
            size,             // size
            data);            // data
}

/**
 * Returns a handle to a new buffer.
 */
GLuint BufferObject::createHandle() {
    
    GLuint handle;
    
    glGenBuffers(1, &handle);
    return handle;
}

// GETTERS AND SETTERS

/**
 * Returns OpenGL's underlying identifier for the buffer.
 */
GLuint BufferObject::getHandle() const {
    return handle;
}

/**
 * Returns type of the buffer.
 */
GLenum BufferObject::getType() const {
    return type;
}
