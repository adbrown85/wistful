/*
 * VertexBufferBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/geometry/VertexBufferBuilder.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates a new builder.
 */
VertexBufferBuilder::VertexBufferBuilder() {
    reset();
}

/**
 * Adds a vertex attribute to the buffer.
 */
void VertexBufferBuilder::addAttribute(const string &name, int size) {
    attributes.push_back(VertexAttribute(name, size));
}

/**
 * Removes all state that was accumulated.
 */
void VertexBufferBuilder::reset() {
    interleaved = true;
    usage = GL_STATIC_DRAW;
    capacity = 0;
    attributes.clear();
}

/**
 * Changes how many vertices the VBO will hold.
 */
void VertexBufferBuilder::setCapacity(GLuint capacity) {
    if (capacity > 0) {
        this->capacity = capacity;
    } else {
        throw Exception("[VertexBufferObjectBuilder] Capacity > 0!");
    }
}

/**
 * Changes whether vertex attributes will be interleaved.
 */
void VertexBufferBuilder::setInterleaved(bool interleaved) {
    this->interleaved = interleaved;
}

/**
 * Changes the hint on how the VBO will be accessed and modified.
 */
void VertexBufferBuilder::setUsage(GLenum usage) {
    switch (usage) {
    case GL_DYNAMIC_DRAW:
    case GL_STATIC_DRAW:
    case GL_STREAM_DRAW:
        this->usage = usage;
        break;
    default:
        throw Exception("[VertexBufferObjectBuilder] Unexpected usage type!");
    }
}

/**
 * Returns VertexBufferObject that was built.
 */
VertexBuffer* VertexBufferBuilder::toVertexBuffer() {
    return VertexBuffer::newInstance((*this));
}

// HELPERS

/**
 * Returns True if all required parts have been specified.
 */
bool VertexBufferBuilder::isComplete() const {
    return (capacity > 0) && (!attributes.empty());
}

// GETTERS AND SETTERS

bool VertexBufferBuilder::isInterleaved() const {
    return interleaved;
}

GLuint VertexBufferBuilder::getCapacity() const {
    return capacity;
}

GLenum VertexBufferBuilder::getUsage() const {
    return usage;
}

map<string,GLuint> VertexBufferBuilder::getOffsets() const {
    
    map<string,GLuint> offsets;
    list<VertexAttribute>::const_iterator it;
    GLuint offset = 0;
    GLsizei attributeSizeInBytes;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        offsets[it->getName()] = offset;
        attributeSizeInBytes = sizeof(GLfloat) * it->getCount();
        if (isInterleaved()) {
            offset += attributeSizeInBytes;
        } else {
            offset += attributeSizeInBytes * getCapacity();
        }
    }
    return offsets;
}

/**
 * Returns total number of bytes in the VertexBufferObject.
 */
GLsizei VertexBufferBuilder::getSizeInBytes() const {
    
    list<VertexAttribute>::const_iterator it;
    GLsizei sizeInBytes = 0;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        sizeInBytes += sizeof(float) * it->getCount();
    }
    return sizeInBytes * getCapacity();
}

/**
 * Returns number of bytes between consecutive vertices.
 */
GLuint VertexBufferBuilder::getStrideInBytes() const {
    
    list<VertexAttribute>::const_iterator it;
    GLuint strideInBytes = 0;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        strideInBytes += sizeof(float) * it->getCount();
    }
    return strideInBytes;
}
