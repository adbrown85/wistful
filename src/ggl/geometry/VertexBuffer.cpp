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
 * @return Pointer to new instance, which should be deleted when done with
 * @throw std::exception if prototype is not complete
 * @throw std::exception if could not allocate instance
 */
VertexBuffer* VertexBuffer::newInstance(const Builder &builder) {
    
    VertexBuffer* instance = new VertexBuffer(builder);
    
    if (instance == NULL) {
        throw Exception("[VertexBuffer] Could not allocate instance!");
    } else {
        return instance;
    }
}

/**
 * Creates a new VBO.
 * 
 * @param vbp Prototype for a vertex buffer
 * @throw std::exception if prototype is not complete
 */
VertexBuffer::VertexBuffer(const Builder &builder) :
        BufferObject(GL_ARRAY_BUFFER) {
    
    names = builder.getNames();
    offsets = builder.getOffsets();
    sizes = builder.getSizes();
    types = builder.getTypes();
    capacity = builder.getCapacity();
    interleaved = builder.isInterleaved();
    usage = builder.getUsage();
    footprint = builder.getSizeInBytes();
    stride = builder.getStrideInBytes();
    
    data = new GLubyte[footprint];
    current = data;
    end = data + footprint;
    extent = current;
    skip = false;
    
    bind();
    BufferObject::allocate(builder.getUsage(), footprint);
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

// NESTED CLASSES

VertexBuffer::Builder::Builder() {
    this->interleaved = true;
    this->usage = GL_STATIC_DRAW;
    this->capacity = 0;
    this->attributes.clear();
}

VertexBuffer::Builder::~Builder() {
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
void VertexBuffer::Builder::addAttribute(const string &name, GLenum type) {
    attributes.push_back(Attribute(name, type));
}

/**
 * Changes how many vertices the VBO will hold.
 */
void VertexBuffer::Builder::setCapacity(GLuint capacity) {
    if (capacity > 0) {
        this->capacity = capacity;
    } else {
        throw Exception("[VertexBufferObjectBuilder] Capacity > 0!");
    }
}

/**
 * Changes whether vertex attributes will be interleaved.
 */
void VertexBuffer::Builder::setInterleaved(bool interleaved) {
    this->interleaved = interleaved;
}

/**
 * Changes the hint on how the VBO will be accessed and modified.
 */
void VertexBuffer::Builder::setUsage(GLenum usage) {
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

bool VertexBuffer::Builder::isInterleaved() const {
    return interleaved;
}

GLuint VertexBuffer::Builder::getCapacity() const {
    return capacity;
}

GLenum VertexBuffer::Builder::getUsage() const {
    return usage;
}

/**
 * Returns the names of all attributes that have been added.
 */
list<string> VertexBuffer::Builder::getNames() const {
    
    list<string> names;
    list<Attribute>::const_iterator it;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        names.push_back(it->getName());
    }
    return names;
}

map<string,GLuint> VertexBuffer::Builder::getOffsets() const {
    
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
map<string,GLuint> VertexBuffer::Builder::getSizes() const {
    
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
GLsizei VertexBuffer::Builder::getSizeInBytes() const {
    
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
GLuint VertexBuffer::Builder::getStrideInBytes() const {
    
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
map<string,GLenum> VertexBuffer::Builder::getTypes() const {
    
    map<string,GLenum> types;
    list<Attribute>::const_iterator it;
    
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        types[it->getName()] = GL_FLOAT;
    }
    return types;
}

/**
 * Returns VertexBufferObject that was built.
 */
VertexBuffer* VertexBuffer::Builder::toVertexBuffer() {
    return VertexBuffer::newInstance(*this);
}

/**
 * Constructs a vertex attribute.
 * 
 * @param name Name of the vertex attribute
 * @param type Type of the vertex attribute, e.g. GL_FLOAT_VEC3
 * @throw std::exception if name is invalid
 * @throw std::exception if type is invalid
 */
VertexBuffer::Builder::Attribute::Attribute(const string &name, GLenum type) {
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
VertexBuffer::Builder::Attribute::~Attribute() {
    ;
}

/**
 * Returns name of the vertex attribute.
 */
string VertexBuffer::Builder::Attribute::getName() const {
    return name;
}

/**
 * Returns the size of the attribute in bytes.
 */
GLuint VertexBuffer::Builder::Attribute::getSizeInBytes() const {
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
GLuint VertexBuffer::Builder::Attribute::getSizeInComponents() const {
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
GLuint VertexBuffer::Builder::Attribute::getType() const {
    return type;
}

/**
 * Checks if a name is legal for an attribute.
 * 
 * @param name Name to check
 * @return True if name is legal
 */
bool VertexBuffer::Builder::Attribute::isValidName(const string &name) {
    return (!name.empty()) || (name.find(' ') != -1);
}

/**
 * Checks if a type is legal for an attribute.
 * 
 * @param type Type to check
 * @return True if type is legal
 */
bool VertexBuffer::Builder::Attribute::isValidType(GLenum type) {
    switch (type) {
    case GL_FLOAT_VEC2:
    case GL_FLOAT_VEC3:
    case GL_FLOAT_VEC4:
        return true;
    default:
        return false;
    }
}


