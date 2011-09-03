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
    attributes.push_back(Attribute(name, size));
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

/**
 * Returns the names of all attributes that have been added.
 */
list<string> VertexBufferBuilder::getNames() const {
    
    list<string> names;
    list<Attribute>::const_iterator it;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        names.push_back(it->getName());
    }
    return names;
}

map<string,GLuint> VertexBufferBuilder::getOffsets() const {
    
    map<string,GLuint> offsets;
    list<Attribute>::const_iterator it;
    GLuint offset = 0;
    GLsizei attributeSizeInBytes;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        offsets[it->getName()] = offset;
        attributeSizeInBytes = sizeof(GLfloat) * it->getSize();
        if (isInterleaved()) {
            offset += attributeSizeInBytes;
        } else {
            offset += attributeSizeInBytes * getCapacity();
        }
    }
    return offsets;
}

/**
 * Returns a mapping of the attributes and their number of components.
 */
map<string,GLuint> VertexBufferBuilder::getSizes() const {
    
    map<string,GLuint> sizes;
    list<Attribute>::const_iterator it;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        sizes[it->getName()] = it->getSize();
    }
    return sizes;
}

/**
 * Returns total number of bytes in the VertexBufferObject.
 */
GLsizei VertexBufferBuilder::getSizeInBytes() const {
    
    list<Attribute>::const_iterator it;
    GLsizei sizeInBytes = 0;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        sizeInBytes += sizeof(float) * it->getSize();
    }
    return sizeInBytes * getCapacity();
}

/**
 * Returns number of bytes between consecutive vertices.
 */
GLuint VertexBufferBuilder::getStrideInBytes() const {
    
    list<Attribute>::const_iterator it;
    GLuint strideInBytes = 0;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        strideInBytes += sizeof(float) * it->getSize();
    }
    return strideInBytes;
}

/**
 * Returns a mapping of the attributes and their primitive types.
 */
map<string,GLenum> VertexBufferBuilder::getTypes() const {
    
    map<string,GLenum> types;
    list<Attribute>::const_iterator it;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        types[it->getName()] = GL_FLOAT;
    }
    return types;
}

// NESTED CLASSES

/**
 * Constructs a vertex attribute.
 * 
 * @param name Name of the vertex attribute
 * @param size Number of components in the vertex attribute
 * @throw std::exception if name is invalid
 * @throw std::exception if size is invalid
 */
VertexBufferBuilder::Attribute::Attribute(const string &name, GLuint size) {
    if (!isValidName(name)) {
        throw Exception("[VertexBufferBuilder] Attribute name is invalid!");
    } else if (!isValidSize(size)){
        throw Exception("[VertexBufferBuilder] Attribute size is invalid!");
    } else {
        this->name = name;
        this->size = size;
    }
}

/**
 * Destroys the vertex attribute.
 */
VertexBufferBuilder::Attribute::~Attribute() {
    ;
}

/**
 * Returns name of the vertex attribute.
 */
string VertexBufferBuilder::Attribute::getName() const {
    return name;
}

/**
 * Returns size of the vertex attribute.
 */
GLuint VertexBufferBuilder::Attribute::getSize() const {
    return size;
}

/**
 * Checks if a name is legal for an attribute.
 * 
 * @param name Name to check
 * @return True if name is legal
 */
bool VertexBufferBuilder::Attribute::isValidName(const string &name) {
    return (!name.empty()) || (name.find(' ') != -1);
}

/**
 * Checks if a size is legal for an attribute.
 * 
 * @param size Size to check
 * @return True if size is legal
 */
bool VertexBufferBuilder::Attribute::isValidSize(GLuint size) {
    return size <= 4;
}

