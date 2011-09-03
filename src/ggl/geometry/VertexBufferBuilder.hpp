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
class VertexBufferBuilder : public VertexBufferPrototype {
public:
    VertexBufferBuilder();
    virtual ~VertexBufferBuilder() {}
    virtual void addAttribute(const std::string &name, int size);
    virtual void reset();
    virtual void setCapacity(GLuint capacity);
    virtual void setInterleaved(bool interleaved);
    virtual void setUsage(GLenum usage);
    virtual VertexBuffer* toVertexBuffer();
// Getters
    virtual GLuint getCapacity() const;
    virtual bool isComplete() const;
    virtual bool isInterleaved() const;
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
    std::list<VertexAttribute> attributes;
};

} /* namespace Ggl */
#endif
