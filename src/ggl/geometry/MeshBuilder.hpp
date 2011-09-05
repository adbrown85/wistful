/*
 * MeshBuilder.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MESHBUILDER_HPP
#define GGL_MESHBUILDER_HPP
#include "ggl/common.h"
#include "ggl/geometry/Mesh.hpp"
#include "ggl/geometry/VertexBuffer.hpp"
namespace Ggl {


/**
 * Utility for creating a mesh.
 */
class MeshBuilder {
public:
    MeshBuilder(GLenum type);
    virtual ~MeshBuilder();
    virtual void add(const std::string&, float, float);
    virtual void add(const std::string&, float, float, float);
    virtual void add(const std::string&, float, float, float, float);
    virtual Mesh* toMesh();
private:
// Nested classes
    class Attribute;
    class AttributeBin;
    class BasicMesh;
    class Vec2Attribute;
    class Vec3Attribute;
    class Vec4Attribute;
// Instance variables
    GLenum type;
    std::map<std::string,AttributeBin*> bins;
// Helpers
    typedef std::map<std::string,AttributeBin*> binmap_t;
    static void fill(VertexBuffer*, const binmap_t&);
    AttributeBin* findBin(const std::string &name, GLenum type);
    static GLuint findSizeInComponents(GLenum type);
    static bool isSupportedType(GLenum type);
};


class MeshBuilder::Attribute {
public:
    Attribute();
    virtual ~Attribute();
    virtual void putInto(VertexBuffer *vbo) = 0;
};


class MeshBuilder::AttributeBin {
public:
    AttributeBin(const std::string &name, GLenum type);
    virtual ~AttributeBin();
    virtual void add(Attribute *attribute);
// Accessors
    virtual Attribute *getAttribute(GLuint i);
    virtual GLenum getType() const;
    virtual size_t getSize() const;
private:
    std::string name;
    GLenum type;
    std::vector<Attribute*> attributes;
};


class MeshBuilder::Vec2Attribute : public MeshBuilder::Attribute {
public:
    Vec2Attribute(float, float);
    virtual ~Vec2Attribute();
    virtual void putInto(VertexBuffer *vbo);
private:
    float x;
    float y;
};


class MeshBuilder::Vec3Attribute : public MeshBuilder::Attribute {
public:
    Vec3Attribute(float, float, float);
    virtual ~Vec3Attribute();
    virtual void putInto(VertexBuffer *vbo);
private:
    float x;
    float y;
    float z;
};


class MeshBuilder::Vec4Attribute : public MeshBuilder::Attribute {
public:
    Vec4Attribute(float, float, float, float);
    virtual ~Vec4Attribute();
    virtual void putInto(VertexBuffer *vbo);
private:
    float x;
    float y;
    float z;
    float w;
};


class MeshBuilder::BasicMesh : public Mesh {
public:
    BasicMesh(VertexBuffer *vbo, GLenum mode);
    virtual ~BasicMesh();
    virtual void bind();
    virtual void draw();
    virtual void unbind();
// Accessors and mutators
    virtual std::list<std::string> getNames() const;
    virtual GLuint getOffset(const std::string &name) const;
    virtual GLuint getSize(const std::string &name) const;
    virtual GLuint getStride() const;
    virtual GLenum getType(const std::string &name) const;
private:
    VertexBuffer *vbo;                 // Buffer storing data
    GLenum mode;                       // Type of geometry, e.g. GL_TRIANGLES
// Constructors
    BasicMesh(const BasicMesh&);
    BasicMesh& operator=(const BasicMesh&);
};

} /* namespace Ggl */
#endif
