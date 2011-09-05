/*
 * BufferObject.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_BUFFEROBJECT_HPP
#define GGL_BUFFEROBJECT_HPP
#include "ggl/common.h"
#include "ggl/Exception.hpp"
namespace Ggl {


/**
 * @brief OpenGL buffer object.
 */
class BufferObject {
public:
    explicit BufferObject(GLenum type);
    virtual ~BufferObject();
    virtual void bind();
    virtual void unbind();
// Getters and setters
    virtual GLuint getHandle() const;
    virtual GLenum getType() const;
protected:
    virtual void allocate(GLenum usage, GLsizei size);
    virtual void update(GLsizei size, GLvoid *data, int offset=0);
private:
    GLuint handle;
    GLenum type;
// Helpers
    static GLuint createHandle();
// Constructors
    BufferObject(const BufferObject&);
    BufferObject& operator=(const BufferObject&);
};

} /* namespace Ggl */
#endif
