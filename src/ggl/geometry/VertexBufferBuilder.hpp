/*
 * VertexBufferBuilder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_VERTEXBUFFERBUILDER_HPP
#define GGL_VERTEXBUFFERBUILDER_HPP
#include "ggl/common.h"
#include "ggl/geometry/VertexAttribute.hpp"
#include "ggl/geometry/VertexBuffer.hpp"
namespace Ggl {


/**
 * @brief <i>Builder</i> for a VertexBuffer.
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
    class Delegate;
// Instance variables
    Delegate *delegate;
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


/**
 * Worker that VertexBufferBuilder delegates to.
 */
class VertexBufferBuilder::Delegate : public VertexBuffer::Prototype {
public:
    static Delegate* newInstance();
    virtual ~Delegate();
    virtual void add(const std::string &name, GLenum type);
    virtual void setCapacity(GLuint capacity);
    virtual void setInterleaved(bool interleaved);
    virtual void setUsage(GLenum usage);
// Getters
    virtual GLuint getCapacity() const;
    virtual bool isInterleaved() const;
    virtual std::list<std::string> getNames() const;
    virtual GLenum getUsage() const;
    virtual GLsizei getSizeInBytes() const;
    virtual std::map<std::string,GLuint> getSizes() const;
    virtual GLuint getStrideInBytes() const;
    virtual std::map<std::string,GLuint> getOffsets() const;
    virtual std::map<std::string,GLenum> getTypes() const;
private:
    bool interleaved;
    GLenum usage;
    GLuint capacity; //FIXME: Should be GLsizei
    std::list<Attribute> attributes;
// Constructors
    Delegate();
};

} /* namespace Ggl */
#endif
