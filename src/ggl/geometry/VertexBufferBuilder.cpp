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
    this->delegate = Delegate::newInstance();
}

VertexBufferBuilder::~VertexBufferBuilder() {
    delete delegate;
}

/**
 * Adds space for a vertex attribute to the buffer.
 * 
 * @param name Name of the vertex attribute
 * @param type Type of the vertex attribute, e.g. GL_FLOAT_VEC3
 * @throw std::exception if name is invalid
 * @throw std::exception if type is invalid
 */
void VertexBufferBuilder::addAttribute(const string &name, GLenum type) {
    delegate->add(name, type);
}

/**
 * Changes how many vertices the VBO will hold.
 */
void VertexBufferBuilder::setCapacity(GLuint capacity) {
    delegate->setCapacity(capacity);
}

/**
 * Changes whether vertex attributes will be interleaved.
 */
void VertexBufferBuilder::setInterleaved(bool interleaved) {
    delegate->setInterleaved(interleaved);
}

/**
 * Changes the hint on how the VBO will be accessed and modified.
 */
void VertexBufferBuilder::setUsage(GLenum usage) {
    delegate->setUsage(usage);
}

/**
 * Returns VertexBufferObject that was built.
 */
VertexBuffer* VertexBufferBuilder::toVertexBuffer() {
    return VertexBuffer::newInstance(*delegate);
}

// NESTED CLASSES

VertexBufferBuilder::Delegate* VertexBufferBuilder::Delegate::newInstance() {
    
    Delegate *instance = new Delegate();
    
    if (instance == NULL) {
        throw Exception("[VertexBufferBuilder] Could not allocate!");
    } else {
        return instance;
    }
}

VertexBufferBuilder::Delegate::Delegate() {
    this->interleaved = true;
    this->usage = GL_STATIC_DRAW;
    this->capacity = 0;
    this->attributes.clear();
}

VertexBufferBuilder::Delegate::~Delegate() {
    ;
}

/**
 * Adds space for a vertex attribute to the buffer.
 * 
 * @param name Name of the vertex attribute
 * @param type Type of the vertex attribute, e.g. GL_FLOAT_VEC3
 * @throw std::exception if name is invalid
 * @throw std::exception if type is invalid
 */
void VertexBufferBuilder::Delegate::add(const string &name, GLenum type) {
    attributes.push_back(Attribute(name, type));
}

/**
 * Changes how many vertices the VBO will hold.
 */
void VertexBufferBuilder::Delegate::setCapacity(GLuint capacity) {
    if (capacity > 0) {
        this->capacity = capacity;
    } else {
        throw Exception("[VertexBufferObjectBuilder] Capacity > 0!");
    }
}

/**
 * Changes whether vertex attributes will be interleaved.
 */
void VertexBufferBuilder::Delegate::setInterleaved(bool interleaved) {
    this->interleaved = interleaved;
}

/**
 * Changes the hint on how the VBO will be accessed and modified.
 */
void VertexBufferBuilder::Delegate::setUsage(GLenum usage) {
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

bool VertexBufferBuilder::Delegate::isInterleaved() const {
    return interleaved;
}

GLuint VertexBufferBuilder::Delegate::getCapacity() const {
    return capacity;
}

GLenum VertexBufferBuilder::Delegate::getUsage() const {
    return usage;
}

/**
 * Returns the names of all attributes that have been added.
 */
list<string> VertexBufferBuilder::Delegate::getNames() const {
    
    list<string> names;
    list<Attribute>::const_iterator it;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        names.push_back(it->getName());
    }
    return names;
}

map<string,GLuint> VertexBufferBuilder::Delegate::getOffsets() const {
    
    map<string,GLuint> offsets;
    list<Attribute>::const_iterator it;
    GLuint offset = 0;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        offsets[it->getName()] = offset;
        if (isInterleaved()) {
            offset += it->getSizeInBytes();
        } else {
            offset += it->getSizeInBytes() * getCapacity();
        }
    }
    return offsets;
}

/**
 * Returns a mapping of the attributes and their number of components.
 */
map<string,GLuint> VertexBufferBuilder::Delegate::getSizes() const {
    
    map<string,GLuint> sizes;
    list<Attribute>::const_iterator it;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        sizes[it->getName()] = it->getSizeInComponents();
    }
    return sizes;
}

/**
 * Returns total number of bytes in the VertexBufferObject.
 */
GLsizei VertexBufferBuilder::Delegate::getSizeInBytes() const {
    
    list<Attribute>::const_iterator it;
    GLsizei sizeInBytes = 0;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        sizeInBytes += it->getSizeInBytes();
    }
    return sizeInBytes * getCapacity();
}

/**
 * Returns number of bytes between consecutive vertices.
 */
GLuint VertexBufferBuilder::Delegate::getStrideInBytes() const {
    
    list<Attribute>::const_iterator it;
    GLuint strideInBytes = 0;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        strideInBytes += it->getSizeInBytes();
    }
    return strideInBytes;
}

/**
 * Returns a mapping of the attributes and their primitive types.
 */
map<string,GLenum> VertexBufferBuilder::Delegate::getTypes() const {
    
    map<string,GLenum> types;
    list<Attribute>::const_iterator it;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        types[it->getName()] = GL_FLOAT;
    }
    return types;
}

/**
 * Constructs a vertex attribute.
 * 
 * @param name Name of the vertex attribute
 * @param type Type of the vertex attribute, e.g. GL_FLOAT_VEC3
 * @throw std::exception if name is invalid
 * @throw std::exception if type is invalid
 */
VertexBufferBuilder::Attribute::Attribute(const string &name, GLenum type) {
    if (!isValidName(name)) {
        throw Exception("[VertexBufferBuilder] Attribute name is invalid!");
    } else if (!isValidType(type)){
        throw Exception("[VertexBufferBuilder] Attribute type is invalid!");
    } else {
        this->name = name;
        this->type = type;
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
 * Returns the size of the attribute in bytes.
 */
GLuint VertexBufferBuilder::Attribute::getSizeInBytes() const {
    switch (type) {
    case GL_FLOAT_VEC2: return SIZEOF_FLOAT_VEC2;
    case GL_FLOAT_VEC3: return SIZEOF_FLOAT_VEC3;
    case GL_FLOAT_VEC4: return SIZEOF_FLOAT_VEC4;
    default:
        throw Exception("Unexpected attribute type!");
    }
}

/**
 * Returns the number of components in the attribute.
 */
GLuint VertexBufferBuilder::Attribute::getSizeInComponents() const {
    switch (type) {
    case GL_FLOAT_VEC2: return 2;
    case GL_FLOAT_VEC3: return 3;
    case GL_FLOAT_VEC4: return 4;
    default:
        throw Exception("Unexpected attribute type!");
    }
}

/**
 * Returns type of the vertex attribute, e.g. GL_FLOAT_VEC3.
 */
GLuint VertexBufferBuilder::Attribute::getType() const {
    return type;
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
 * Checks if a type is legal for an attribute.
 * 
 * @param type Type to check
 * @return True if type is legal
 */
bool VertexBufferBuilder::Attribute::isValidType(GLenum type) {
    switch (type) {
    case GL_FLOAT_VEC2:
    case GL_FLOAT_VEC3:
    case GL_FLOAT_VEC4:
        return true;
    default:
        return false;
    }
}

