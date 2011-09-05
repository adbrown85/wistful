/*
 * Mesh.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MESH_HPP
#define GGL_MESH_HPP
#include "ggl/common.h"
namespace Ggl {


/**
 * @brief Polygonal geometry that can be drawn.
 * 
 * Mesh represents reusable geometry data in a Vertex Buffer Object.  In order
 * to be as versatile as possible, the scope of Mesh is fairly limited.  It
 * knows about its vertex attributes and can draw itself, in the sense that it
 * knows how to call <i>glDrawArrays</i>, etc., but it cannot completely render
 * itself.  In other words, it does not have a shader program to activate and
 * it does not know how to enable vertex attributes.  Although this may make
 * things harder for simple cases, by leaving these details up to the
 * application developer we make Mesh more usable in more situations.  For
 * example, this way Mesh can be rendered with more than one shader program.
 * Plus, the developer is free to choose whether to use Vertex Array Objects
 * or not.
 * 
 * To make a Mesh, first create one using MeshBuilder.  To render it, make a
 * shader program and query the locations of the vertex attributes in it using
 * <i>glGetAttribLocation</i>.   Next, bind the mesh and use those locations in
 * calls to <i>glVertexAttribPointer</i> and <i>glEnableVertexAttribArray</i>.
 * Lastly, activate the program with <i>glUseProgram</i> and draw the mesh.
 * Although not required, using a Vertex Array Object to store the state of
 * enabled vertex attributes may make drawing the mesh easier and faster.
 */
class Mesh {
public:
    Mesh();
    virtual ~Mesh();
    virtual void bind() = 0;
    virtual void draw() = 0;
    virtual void unbind() = 0;
// Getters and setters
    virtual bool hasAttribute(const std::string &name) const = 0;
    virtual std::list<std::string> getAttributeNames() const = 0;
    virtual GLuint getAttributeOffset(const std::string &name) const = 0;
    virtual GLuint getAttributeSize(const std::string &name) const = 0;
    virtual GLenum getAttributeType(const std::string &name) const = 0;
    virtual GLuint getStride() const = 0;
private:
// Constructors
    Mesh(const Mesh&);
    Mesh& operator=(const Mesh&);
};

} /* namespace Ggl */
#endif
