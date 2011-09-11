/*
 * VertexBuffer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/geometry/VertexBuffer.hpp"
using namespace std;
using namespace Edo;
using namespace Ggl;

/**
 * Constructs a vertex buffer object.
 * 
 * @param prototype Prototype for a vertex buffer object
 */
VertexBuffer::VertexBuffer(const Prototype &prototype) :
        BufferObject(GL_ARRAY_BUFFER) {
    
    names = findNames(prototype);
    offsets = findOffsets(prototype);
    sizes = findSizes(prototype);
    types = findTypes(prototype);
    capacity = prototype.capacity;
    interleaved = prototype.interleaved;
    usage = prototype.usage;
    footprint = findSizeInBytes(prototype);
    stride = findStrideInBytes(prototype);
    
    data = new GLubyte[footprint];
    current = data;
    end = data + footprint;
    extent = current;
    skip = false;
    
    bind();
    BufferObject::allocate(prototype.usage, footprint);
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
        throw Exception("[VertexBuffer] Attribute not stored!");
    }
    
    // Enable skipping
    skip = true;
}

// GETTERS AND SETTERS

/**
 * Returns the names of all attributes in the VBO.
 */
list<string> VertexBuffer::getAttributeNames() const {
    return names;
}

/**
 * Determines the position of an attribute in the VBO.
 * 
 * @param name Name of an attribute
 * @return Position of the attribute in the VBO
 * @throw std::exception if attribute is not in the VBO 
 */
GLuint VertexBuffer::getAttributeOffset(const string &name) const {
    
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
GLuint VertexBuffer::getAttributeSize(const string &name) const {
    
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
GLenum VertexBuffer::getAttributeType(const string &name) const {
    
    map<string,GLenum>::const_iterator it;
    
    it = types.find(name);
    if (it != types.end()) {
        return it->second;
    } else {
        throw Exception("[VertexBuffer] Attribute is not stored!");
    }
}

/**
 * Returns number of vertices the VBO can hold.
 */
GLuint VertexBuffer::getCapacity() const {
    return capacity;
}

/**
 * Returns size in bytes of the VBO.
 */
GLsizei VertexBuffer::getFootprint() const {
    return footprint;
}

/**
 * Returns number of bytes between vertices.
 */
GLuint VertexBuffer::getStride() const {
    return stride;
}

/**
 * Returns true if this VBO keeps all attributes of a vertex together.
 */
bool VertexBuffer::isInterleaved() const {
    return interleaved;
}

/**
 * Returns number of vertices stored in the VBO.
 */
GLuint VertexBuffer::size() const {
    return (extent - current) / stride;
}

// HELPERS

/**
 * Determines the names of the attributes in a list.
 *
 * @param p Prototype with list of attributes
 * @return List of attribute names
 */
list<string> VertexBuffer::findNames(const Prototype &p) {
    
    list<string> names;
    list<Attribute>::const_iterator it;
    
    for (it=p.attributes.begin(); it!=p.attributes.end(); ++it) {
        names.push_back(it->getName());
    }
    return names;
}

/**
 * Computes the offsets of attributes.
 *
 * @param p Prototype with list of attributes to compute offsets of
 * @return Mapping of attribute names to their offsets
 */
map<string,GLuint> VertexBuffer::findOffsets(const Prototype &p) {
    
    map<string,GLuint> offsets;
    list<Attribute>::const_iterator it;
    GLuint offset = 0;
    
    for (it=p.attributes.begin(); it!=p.attributes.end(); ++it) {
        offsets[it->getName()] = offset;
        if (p.interleaved) {
            offset += it->getSizeInBytes();
        } else {
            offset += it->getSizeInBytes() * p.capacity;
        }
    }
    return offsets;
}

/**
 * Computes the sizes of attributes.
 *
 * @param p Prototype with list of attributes to computes sizes of
 * @return Mapping of the attributes and their number of components.
 */
map<string,GLuint> VertexBuffer::findSizes(const Prototype &p) {
    
    map<string,GLuint> sizes;
    list<Attribute>::const_iterator it;
    
    for (it=p.attributes.begin(); it!=p.attributes.end(); ++it) {
        sizes[it->getName()] = it->getSizeInComponents();
    }
    return sizes;
}

/**
 * Computes the total number of bytes needed by multiple attributes.
 *
 * @param p Prototype with list of attributes to compute sizes for
 * @return Total number of bytes in the vertex buffer
 */
GLsizei VertexBuffer::findSizeInBytes(const Prototype &p) {
    
    list<Attribute>::const_iterator it;
    GLsizei sizeInBytes = 0;
    
    for (it=p.attributes.begin(); it!=p.attributes.end(); ++it) {
        sizeInBytes += it->getSizeInBytes();
    }
    return sizeInBytes * p.capacity;
}

/**
 * Computes the stride of the vertex buffer.
 *
 * @param p Prototype with list of attributes to compute stride with
 * @return Number of bytes between consecutive vertices
 */
GLuint VertexBuffer::findStrideInBytes(const Prototype &p) {
    
    list<Attribute>::const_iterator it;
    GLuint strideInBytes = 0;
    
    for (it=p.attributes.begin(); it!=p.attributes.end(); ++it) {
        strideInBytes += it->getSizeInBytes();
    }
    return strideInBytes;
}

/**
 * Returns a mapping of the attributes and their primitive types.
 *
 * @param p Prototype with list of attributes to determine primitive types of
 * @return Mapping of attribute names with their types
 */
map<string,GLenum> VertexBuffer::findTypes(const Prototype &p) {
    
    map<string,GLenum> types;
    list<Attribute>::const_iterator it;
    
    for (it=p.attributes.begin(); it!=p.attributes.end(); ++it) {
        types[it->getName()] = GL_FLOAT;
    }
    return types;
}

// NESTED CLASSES

VertexBufferBuilder::VertexBufferBuilder() {
    this->prototype.interleaved = true;
    this->prototype.usage = GL_STATIC_DRAW;
    this->prototype.capacity = 0;
    this->prototype.attributes.clear();
}

VertexBufferBuilder::~VertexBufferBuilder() {
    ;
}

/**
 * Adds space for a vertex attribute to the VBO.
 * 
 * @param name Name of the vertex attribute
 * @param type Type of the vertex attribute, e.g. GL_FLOAT_VEC3
 * @throw std::exception if name is invalid
 * @throw std::exception if type is invalid
 */
void VertexBufferBuilder::addAttribute(const string &name, GLenum type) {
    prototype.attributes.push_back(VertexBuffer::Attribute(name, type));
}

/**
 * Changes how many vertices the VBO will hold.
 *
 * @param capacity How many vertices the vbo will hold
 * @throw std::exception if capacity is zero
 */
void VertexBufferBuilder::setCapacity(GLuint capacity) {
    if (capacity == 0) {
        throw Exception("[VertexBufferBuilder] Capacity is zero!");
    } else {
        prototype.capacity = capacity;
    }
}

/**
 * Changes whether vertex attributes will be interleaved.
 *
 * @param interleaved <tt>true</tt> if attributes should be interleaved
 */
void VertexBufferBuilder::setInterleaved(bool interleaved) {
    prototype.interleaved = interleaved;
}

/**
 * Changes the hint on how the VBO will be accessed and modified.
 *
 * @param usage Hint for how VBO will be used, e.g. GL_STATIC_DRAW
 * @throw std::exception if usage is unexpected
 */
void VertexBufferBuilder::setUsage(GLenum usage) {
    switch (usage) {
    case GL_DYNAMIC_DRAW:
    case GL_STATIC_DRAW:
    case GL_STREAM_DRAW:
        prototype.usage = usage;
        break;
    default:
        throw Exception("[VertexBuffer] Unexpected usage type!");
    }
}

/**
 * Returns Vertex Buffer Object that was built.
 * 
 * @throw std::exception if no attributes were added
 * @throw std::exception if capacity has not been set
 */
VertexBuffer* VertexBufferBuilder::toVertexBuffer() {
    if (prototype.attributes.empty()) {
        throw Exception("[VertexBuffer] No attributes were added!");
    } else if (prototype.capacity == 0) {
        throw Exception("[VertexBuffer] Capacity was not set!");
    } else {
        return new VertexBuffer(prototype);
    }
}

/**
 * Constructs a vertex attribute.
 * 
 * @param name Name of the vertex attribute
 * @param type Type of the vertex attribute, e.g. GL_FLOAT_VEC3
 * @throw std::exception if name is invalid
 * @throw std::exception if type is invalid
 */
VertexBuffer::Attribute::Attribute(const string &name, GLenum type) {
    if (!isValidName(name)) {
        throw Exception("[VertexBuffer] Attribute name is invalid!");
    } else if (!isValidType(type)){
        throw Exception("[VertexBuffer] Attribute type is invalid!");
    } else {
        this->name = name;
        this->type = type;
    }
}

/**
 * Destroys the vertex attribute.
 */
VertexBuffer::Attribute::~Attribute() {
    ;
}

/**
 * Returns name of the vertex attribute.
 */
string VertexBuffer::Attribute::getName() const {
    return name;
}

/**
 * Returns the size of the attribute in bytes.
 */
GLuint VertexBuffer::Attribute::getSizeInBytes() const {
    switch (type) {
    case GL_FLOAT_VEC2: return SIZEOF_FLOAT_VEC2;
    case GL_FLOAT_VEC3: return SIZEOF_FLOAT_VEC3;
    case GL_FLOAT_VEC4: return SIZEOF_FLOAT_VEC4;
    default:
        throw Exception("[VertexBuffer] Unexpected attribute type!");
    }
}

/**
 * Returns the number of components in the attribute.
 */
GLuint VertexBuffer::Attribute::getSizeInComponents() const {
    switch (type) {
    case GL_FLOAT_VEC2: return 2;
    case GL_FLOAT_VEC3: return 3;
    case GL_FLOAT_VEC4: return 4;
    default:
        throw Exception("[VertexBuffer] Unexpected attribute type!");
    }
}

/**
 * Returns type of the vertex attribute, e.g. GL_FLOAT_VEC3.
 */
GLuint VertexBuffer::Attribute::getType() const {
    return type;
}

/**
 * Checks if a name is legal for an attribute.
 * 
 * @param name Name to check
 * @return True if name is legal
 */
bool VertexBuffer::Attribute::isValidName(const string &name) {
    return (!name.empty()) || (name.find(' ') != -1);
}

/**
 * Checks if a type is legal for an attribute.
 * 
 * @param type Type to check
 * @return True if type is legal
 */
bool VertexBuffer::Attribute::isValidType(GLenum type) {
    switch (type) {
    case GL_FLOAT_VEC2:
    case GL_FLOAT_VEC3:
    case GL_FLOAT_VEC4:
        return true;
    default:
        return false;
    }
}


