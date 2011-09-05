/*
 * Mesh.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/geometry/Mesh.hpp"
using namespace Ggl;
using std::list;
using std::string;

/**
 * Constructs a mesh.
 */
Mesh::Mesh() {
    ;
}

/**
 * Destroys the mesh.
 */
Mesh::~Mesh() {
    ;
}

/**
 * Activates the mesh.
 */
void Mesh::bind() {
    // Dummy implementation used just for documentation
}

/**
 * Draws the mesh.
 */
void Mesh::draw() {
    // Dummy implementation used just for documentation
}

/**
 * Deactivates the mesh.
 */
void Mesh::unbind() {
    // Dummy implementation used just for documentation
}

/* GETTERS AND SETTERS */

/**
 * Returns the names of all attributes in the mesh.
 */
list<string> Mesh::getAttributeNames() const {
    // Dummy implementation used just for documentation
    list<string> names;
    return names;
}

/**
 * Determines the position of an attribute in the mesh.
 * 
 * The offset of the vertex attribute is the byte offset from the start of the
 * underlying OpenGL Vertex Buffer Object to the first value for the vertex
 * attribute.  The resulting position can be used as the last argument in a
 * call to <i>glVertexAttribPointer</i>.
 * 
 * @param name Name of an attribute
 * @return Position of the attribute in the mesh
 * @throw std::exception if attribute is not in the mesh
 */
GLuint Mesh::getAttributeOffset(const std::string &name) const {
    // Dummy implementation used just for documentation
    return -1;
}

/**
 * Determines the number of components of an attribute in the mesh.
 * 
 * The number of components of a vertex attribute is how many primitive values
 * are in the vector that makes up a single vertex attribute value.  The result
 * will be <tt>1</tt>, <tt>2</tt>, <tt>3</tt>, or <tt>4</tt>, and can be used
 * directly in a call to <i>glVertexAttribPointer</i>.
 * 
 * @param name Name of an attribute
 * @return Number of components of the attribute in the mesh
 * @throw std::exception if attribute is not in the mesh
 */
GLuint Mesh::getAttributeSize(const string &name) const {
    // Dummy implementation used just for documentation
    return -1;
}

/**
 * Determines the primitive type of an attribute in the mesh.
 * 
 * The primitive value of a vertex attribute is the kind of values that make
 * up the vector for a value of the vertex attribute.  In other words it is
 * the type of the vector with no dimension.  For example, if the type of the
 * vertex attribute is <tt>GL_FLOAT_VEC3</tt>, the resulting value will be
 * <tt>GL_FLOAT</tt>.  It can be used directly in a call to
 * <i>glVertexAttribPointer</i>.
 * 
 * @param name Name of an attribute
 * @return Primitive type of the attribute, e.g. GL_FLOAT
 * @throw std::exception if attribute is not in the mesh
 */
GLenum Mesh::getAttributeType(const std::string &name) const {
    // Dummy implementation used just for documentation
    return -1;
}

/**
 * Returns the number of bytes needed to move from one vertex to the next.
 * 
 * The stride of a vertex is how many bytes OpenGL needs to skip over to get
 * from a value for a vertex attribute of one vertex to the value of the
 * same vertex attribute of the next vertex.  If the underlying Vertex Buffer
 * Object is interleaved, the value will be the size of one vertex in bytes.
 * If the underlying Vertex Buffer Object is not interleaved, the value will
 * be <tt>0</tt>, meaning that the vertex attribute values are tightly
 * packed.  The resulting value can be used directly in a call to
 * <i>glVertexAttribPointer</i>.
 */
GLuint Mesh::getStride() const {
    // Dummy implementation used just for documentation
    return -1;
}
