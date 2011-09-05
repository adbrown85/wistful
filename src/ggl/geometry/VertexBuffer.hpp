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
 * @brief OpenGL buffer object for vertex attributes.
 * 
 * To create a VertexBuffer, use VertexBufferObject::Builder.  Then
 * use the variations of put() to fill the buffer.  Finally, call flush()
 * to send the data to the card.
 * 
 * To update data, call rewind() to go back to the beginning of the buffer and
 * then call the put() methods again to overwrite the data in the buffer.  
 * Remember to call flush() when you are done.
 * 
 * Lastly, if you would like to update just one attribute, call 
 * setStriding() before making any calls to put.  
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
    bool isInterleaved() const;
    GLuint getCapacity() const;
    GLsizei getFootprint() const;
    std::list<std::string> getNames() const;
    GLuint getOffset(const std::string &name) const;
    GLuint size() const;
    GLuint getSize(const std::string &name) const;
    GLuint getStride() const;
    GLenum getType(const std::string &name) const;
// Nested classes
    class Builder;
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
// Constructors
    VertexBuffer(const Builder &builder);
    VertexBuffer(const VertexBuffer&);
    VertexBuffer& operator=(const VertexBuffer&);
};


/**
 * Utility for making a vertex buffer.
 */
class VertexBuffer::Builder {
public:
    Builder();
    virtual ~Builder();
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
// Getters
    virtual GLuint getCapacity() const;
    virtual bool isInterleaved() const;
    virtual std::map<std::string,GLuint> getOffsets() const;
    virtual std::list<std::string> getNames() const;
    virtual std::map<std::string,GLuint> getSizes() const;
    virtual GLsizei getSizeInBytes() const;
    virtual GLuint getStrideInBytes() const;
    virtual std::map<std::string,GLenum> getTypes() const;
    virtual GLenum getUsage() const;
// Friends
    friend class VertexBuffer;
};


/**
 * Vertex attribute added to the builder.
 */
class VertexBuffer::Builder::Attribute {
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
