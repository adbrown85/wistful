/*
 * VertexBuffer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/geometry/VertexBuffer.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates a new VBO.
 * 
 * @param vbp Prototype for a vertex buffer
 * @throw std::exception if prototype is not complete 
 */
VertexBuffer* VertexBuffer::newInstance(const VertexBufferPrototype &vbp) {
    if (!vbp.isComplete()) {
        throw Exception("[VertexBufferObject] Prototype is not complete!");
    } else {
        return new VertexBuffer(vbp);
    }
}

/**
 * Creates a new VBO.
 * 
 * @param vbp Prototype for a vertex buffer
 * @throw std::exception if prototype is not complete
 */
VertexBuffer::VertexBuffer(const VertexBufferPrototype &vbp) :
        BufferObject(GL_ARRAY_BUFFER) {
    
    names = vbp.getNames();
    offsets = vbp.getOffsets();
    sizes = vbp.getSizes();
    types = vbp.getTypes();
    capacity = vbp.getCapacity();
    interleaved = vbp.isInterleaved();
    usage = vbp.getUsage();
    footprint = vbp.getSizeInBytes();
    stride = vbp.getStrideInBytes();
    
    data = new GLubyte[footprint];
    current = data;
    end = data + footprint;
    extent = current;
    skip = false;
    
    bind();
    BufferObject::allocate(vbp.getUsage(), footprint);
    unbind();
}

/**
 * Destroys the data held by the VBO.
 */
VertexBuffer::~VertexBuffer() {
    if (data != NULL) {
        delete[] data;
    }
}

/**
 * Sends the data to the video card.
 */
void VertexBuffer::flush() {
    BufferObject::update(footprint, data, 0);
    skip = false;
}

/**
 * Specifies the value of a vertex for the current attribute.
 * 
 * @param x Value for first component
 * @param y Value for second component
 * @throw std::exception if attribute would exceed buffer
 */
void VertexBuffer::put(float x, float y) {
    
    if ((current + SIZEOF_VEC2) > end) {
        throw Exception("[VertexBuffer] Put would exceed buffer!");
    }
    
    ((GLfloat*) current)[0] = x;
    ((GLfloat*) current)[1] = y;
    current += skip ? stride : SIZEOF_VEC2;
    if (current > extent) extent = current;
}

/**
 * Specifies the value of a vertex for the current attribute.
 * 
 * @param x Value for first component
 * @param y Value for second component
 * @param z Value for third component
 * @throw std::exception if attribute would exceed buffer
 */
void VertexBuffer::put(float x, float y, float z) {
    
    if ((current + SIZEOF_VEC3) > end) {
        throw Exception("[VertexBuffer] Put would exceed buffer!");
    }
    
    ((GLfloat*)current)[0] = x;
    ((GLfloat*)current)[1] = y;
    ((GLfloat*)current)[2] = z;
    current += skip ? stride : SIZEOF_VEC3;
    if (current > extent) extent = current;
}

/**
 * Specifies the value of a vertex for the current attribute.
 * 
 * @param x Value for first component
 * @param y Value for second component
 * @param z Value for third component
 * @param w Value for fourth component
 * @throw std::exception if attribute would exceed buffer
 */
void VertexBuffer::put(float x, float y, float z, float w) {
    
    if ((current + SIZEOF_VEC4) > end) {
        throw Exception("[VertexBuffer] Put would exceed buffer!");
    }
    
    ((GLfloat*)current)[0] = x;
    ((GLfloat*)current)[1] = y;
    ((GLfloat*)current)[2] = z;
    ((GLfloat*)current)[3] = w;
    current += skip ? stride : SIZEOF_VEC4;
    if (current > extent) extent = current;
}

/**
 * Returns position to beginning and marks data as unused.
 */
void VertexBuffer::reset() {
    current = data;
    skip = false;
    extent = current;
}

/**
 * Returns the current position to the beginning of the buffer.
 */
void VertexBuffer::rewind() {
    current = data;
    skip = false;
}

/**
 * Moves to the start of an attribute.
 * 
 * In addition, when the buffer is interleaved, subsequent calls to any
 * of the put methods will cause the buffer's internal marker to jump
 * to the next vertex of the same attribute.  This method should be
 * used to update all vertices of a single attribute.  Normal behavior
 * will be restored after the buffer is rewound or flushed.
 * 
 * @param name Name of attribute
 * @throw std::exception if attribute is not stored
 */
void VertexBuffer::seek(const string &name) {
    
    map<string,GLuint>::iterator it;
    
    // Find offset and add it to data
    it = offsets.find(name);
    if (it != offsets.end()) {
        current = data + it->second;
    } else {
        throw Exception("[VertexBufferObject] Attribute not stored!");
    }
    
    // Enable skipping
    skip = true;
}

// GETTERS AND SETTERS

/**
 * Returns the names of all attributes in the VBO.
 */
list<string> VertexBuffer::getNames() const {
    return names;
}

/**
 * Determines the position of an attribute in the VBO.
 * 
 * @param name Name of an attribute
 * @return Position of the attribute in the VBO
 * @throw std::exception if attribute is not in the VBO 
 */
GLuint VertexBuffer::getOffset(const string &name) const {
    
    map<string,GLuint>::const_iterator it;
    
    it = offsets.find(name);
    if (it != offsets.end()) {
        return it->second;
    } else {
        throw Exception("[VertexBuffer] Attribute is not stored!");
    }
}

/**
 * Returns number of components of an attribute in the VBO.
 * 
 * @param name Name of an attribute
 * @return Size of the attribute in components
 * @throw std::exception if attribute is not in the VBO
 */
GLuint VertexBuffer::getSize(const string &name) const {
    
    map<string,GLuint>::const_iterator it;
    
    it = sizes.find(name);
    if (it != sizes.end()) {
        return it->second;
    } else {
        throw Exception("[VertexBuffer] Attribute is not stored!");
    }
}

/**
 * Determines the primitive type of an attribute.
 * 
 * @param name Name of an attribute
 * @return Primitive type of the attribute, e.g. GL_FLOAT
 * @throw std::exception if attribute is not in the VBO
 */
GLenum VertexBuffer::getType(const string &name) const {
    
    map<string,GLenum>::const_iterator it;
    
    it = types.find(name);
    if (it != types.end()) {
        return it->second;
    } else {
        throw Exception("[VertexBuffer] Attribute is not stored!");
    }
}

/**
 * Returns number of vertices stored in the VBO.
 */
GLuint VertexBuffer::size() const {
    return (extent - current) / stride;
}
