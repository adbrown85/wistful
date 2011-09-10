/*
 * VertexBuffer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_VERTEXBUFFER_HPP
#define GGL_VERTEXBUFFER_HPP
#include "ggl/common.h"
#include "ggl/Exception.hpp"
#include "ggl/geometry/BufferObject.hpp"
namespace Ggl {


/**
 * OpenGL buffer object for vertex attributes.
 * 
 * To create a VertexBuffer, use VertexBufferBuilder.  Then use the variations
 * of put() to fill the buffer.  Finally, call flush() to send the data to the
 * card.
 * 
 * To update data, call rewind() to go back to the beginning of the buffer and
 * then call the put() methods again to overwrite the data in the buffer.  
 * Remember to call flush() when you are done.
 * 
 * Lastly, if you would like to update just one attribute, call 
 * setStriding() before making any calls to put.
 * 
 * @ingroup geometry
 */
class VertexBuffer : public BufferObject {
public:
    virtual ~VertexBuffer();
    void put(float x, float y);
    void put(float x, float y, float z);
    void put(float x, float y, float z, float w);
    void flush();
    void reset();
    void rewind();
    void seek(const std::string &name);
// Getters and setters
    std::list<std::string> getAttributeNames() const;
    GLuint getAttributeOffset(const std::string &name) const;
    GLuint getAttributeSize(const std::string &name) const;
    GLenum getAttributeType(const std::string &name) const;
    bool isInterleaved() const;
    GLuint getCapacity() const;
    GLsizei getFootprint() const;
    GLuint size() const;
    GLuint getStride() const;
private:
// Instance variables
    bool interleaved;                  // Whether attributes are mixed together
    bool skip;                         // Whether to jump to next vertex
    GLubyte *data;                     // Start of attribute memory
    GLubyte *current;                  // Memory location to put next attribute
    GLubyte *end;                      // End of attribute memory
    GLubyte *extent;                   // Farthest attributes have been put
    GLuint capacity;                   // Number of vertices VBO can store
    GLuint stride;                     // Number of bytes between vertices
    GLsizei footprint;                 // Size in bytes of total VBO
    GLenum usage;                      // Hint for how VBO is read and updated
    std::list<std::string> names;
    std::map<std::string,GLuint> sizes;
    std::map<std::string,GLuint> offsets;
    std::map<std::string,GLenum> types;
// Constants
    static const int SIZEOF_VEC2 = sizeof(float) * 2;
    static const int SIZEOF_VEC3 = sizeof(float) * 3;
    static const int SIZEOF_VEC4 = sizeof(float) * 4;
// Nested classes
    class Prototype;
// Constructors
    VertexBuffer(const Prototype &prototype);
    VertexBuffer(const VertexBuffer&);
    VertexBuffer& operator=(const VertexBuffer&);
// Friends
    friend class VertexBufferBuilder;
};


/**
 * Parameters for making a vertex buffer.
 */
struct VertexBuffer::Prototype {
    GLuint capacity;
    bool interleaved;
    std::list<std::string> names;
    std::map<std::string,GLuint> offsets;
    std::map<std::string,GLuint> sizes; 
    GLuint sizeInBytes;
    GLuint strideInBytes;
    std::map<std::string,GLenum> types;
    GLenum usage;
};


/**
 * Utility for making a vertex buffer.
 *
 * @ingroup geometry
 */
class VertexBufferBuilder {
public:
    VertexBufferBuilder();
    virtual ~VertexBufferBuilder();
    virtual void addAttribute(const std::string &name, GLenum type);
    virtual void setCapacity(GLuint capacity);
    virtual void setInterleaved(bool interleaved);
    virtual void setUsage(GLenum usage);
    virtual VertexBuffer* toVertexBuffer();
private:
// Nested classes
    class Attribute;
// Instance variables
    bool interleaved;
    GLenum usage;
    GLuint capacity; //FIXME: Should be GLsizei
    std::list<Attribute> attributes;
// Helpers
    VertexBuffer::Prototype createPrototype() const;
    GLuint getCapacity() const;
    bool isInterleaved() const;
    std::map<std::string,GLuint> getOffsets() const;
    std::list<std::string> getNames() const;
    std::map<std::string,GLuint> getSizes() const;
    GLsizei getSizeInBytes() const;
    GLuint getStrideInBytes() const;
    std::map<std::string,GLenum> getTypes() const;
    GLenum getUsage() const;
};


/**
 * Vertex attribute added to the builder.
 */
class VertexBufferBuilder::Attribute {
public:
    Attribute(const std::string &name, GLenum type);
    virtual ~Attribute();
// Getters and setters
    virtual std::string getName() const;
    virtual GLuint getSizeInBytes() const;
    virtual GLuint getSizeInComponents() const;
    virtual GLenum getType() const;
private:
    std::string name;
    GLenum type;
// Constants
    static const GLuint SIZEOF_FLOAT_VEC2 = sizeof(GLfloat) * 2;
    static const GLuint SIZEOF_FLOAT_VEC3 = sizeof(GLfloat) * 3;
    static const GLuint SIZEOF_FLOAT_VEC4 = sizeof(GLfloat) * 4;
// Helpers
    static bool isValidName(const std::string &name);
    static bool isValidType(GLenum type);
};

} /* namespace Ggl */
#endif
