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
#include "ggl/geometry/VertexAttribute.hpp"
namespace Ggl {


/* Parameters to create a vertex buffer. */ 
class VertexBufferPrototype {
public:
    virtual bool isComplete() const = 0;
    virtual std::map<std::string,GLuint> getOffsets() const = 0;
    virtual GLuint getCapacity() const = 0;
    virtual bool isInterleaved() const = 0;
    virtual std::list<std::string> getNames() const = 0;
    virtual GLenum getUsage() const = 0;
    virtual std::map<std::string,GLuint> getSizes() const = 0;
    virtual std::map<std::string,GLenum> getTypes() const = 0;
    virtual GLsizei getSizeInBytes() const = 0;
    virtual GLuint getStrideInBytes() const = 0;
};


/**
 * @brief OpenGL buffer object for vertex attributes.
 * 
 * To create a VertexBufferObject, use VertexBufferObjectBuilder.  Then 
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
    static VertexBuffer* newInstance(const VertexBufferPrototype &vbp);
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
private:
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
    VertexBuffer(const VertexBufferPrototype &vbd);
};

/** Returns number of vertices the VBO can hold. */
inline GLuint VertexBuffer::getCapacity() const {return capacity;}

/** Returns size in bytes of the VBO. */
inline GLsizei VertexBuffer::getFootprint() const {return footprint;}

/** Returns number of bytes between vertices. */
inline GLuint VertexBuffer::getStride() const {return stride;}

/** Returns true if this VBO keeps all attributes of a vertex together. */
inline bool VertexBuffer::isInterleaved() const {return interleaved;}

} /* namespace Ggl */
#endif
