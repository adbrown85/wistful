/*
 * MeshBuilder.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/geometry/MeshBuilder.hpp"
using namespace Ggl;
using namespace std;

/**
 * Constructs a mesh builder.
 * 
 * @param type Type of geometry, e.g. GL_TRIANGLES
 * @throw std::exception if type is unsupported
 */
MeshBuilder::MeshBuilder(GLenum type) {
    if (!isSupportedType(type)) {
        throw Exception("Type is unsupported!");
    } else {
        this->type = type;
        this->bins.clear();
    }
}

/**
 * Destroys the mesh builder.
 */
MeshBuilder::~MeshBuilder() {
    
    map<string,AttributeBin*>::iterator it = bins.begin();
    
    while (it != bins.end()) {
        delete (it->second);
        ++it;
    }
}

/**
 * Stores a two-component attribute in the mesh.
 * 
 * @param name Name of the attribute as specified in shader
 * @param x Value of first component
 * @param y Value of second component
 * @throw std::exception if name is empty
 */
void MeshBuilder::add(const string &name, float x, float y) {
    findBin(name, GL_FLOAT_VEC2)->add(new Vec2Attribute(x, y));
}

/**
 * Stores a three-component attribute in the mesh.
 * 
 * @param name Name of the attribute as specified in shader
 * @param x Value of first component
 * @param y Value of second component
 * @param z Value of third component
 * @throw std::exception if name is empty
 */
void MeshBuilder::add(const string &name, float x, float y, float z) {
    findBin(name, GL_FLOAT_VEC3)->add(new Vec3Attribute(x, y, z));
}

/**
 * Stores a four-component attribute in the mesh.
 * 
 * @param name Name of the attribute as specified in shader
 * @param x Value of first component
 * @param y Value of second component
 * @param z Value of third component
 * @param w Value of fourth component
 * @throw std::exception if name is empty
 */
void MeshBuilder::add(const string &name, float x, float y, float z, float w) {
    findBin(name, GL_FLOAT_VEC4)->add(new Vec4Attribute(x, y, z, w));
}

/**
 * Finishes building the mesh.
 * 
 * @return Pointer to a new mesh
 * @throw std::exception if no attributes were added
 * @throw std::exception if one or more vertices is missing attributes
 * @throw std::exception if attribute is missing values
 */
Mesh* MeshBuilder::toMesh() {
    
    VertexBuffer::Builder vbb;
    VertexBuffer *vbo;
    map<string,AttributeBin*>::iterator it;
    size_t size;
    
    // Validate
    if (bins.empty()) {
        throw Exception("[MeshBuilder] No attributes were added!");
    }
    
    // Add the attributes
    for (it=bins.begin(); it!=bins.end(); ++it) {
        vbb.addAttribute(it->first, it->second->getType());
    }
    
    // Determine size
    it = bins.begin();
    size = it->second->getSize();
    ++it;
    while (it != bins.end()) {
        if (it->second->getSize() != size) {
            throw Exception("[MeshBuilder] Attribute is missing values!");
        }
        ++it;
    }
    vbb.setCapacity(size);
    
    // Change other characteristics
    vbb.setUsage(GL_STATIC_DRAW);
    vbb.setInterleaved(true);
    
    // Make and fill the buffer
    vbo = vbb.toVertexBuffer();
    fill(vbo, bins);
    
    return new BasicMesh(vbo, type);
}

/* HELPERS */

void MeshBuilder::fill(VertexBuffer *vbo, const binmap_t &bins) {
    
    map<string,AttributeBin*>::const_iterator it;
    GLuint count = vbo->getCapacity();
    Attribute *attribute;
    
    vbo->bind();
    for (int i=0; i<count; ++i) {
        for (it=bins.begin(); it!=bins.end(); ++it) {
            attribute = it->second->getAttribute(i);
            attribute->putInto(vbo);
        }
    }
    vbo->flush();
    vbo->unbind();
}

/**
 * Retrieves the bin for an attribute.
 * 
 * @param name Name of the attribute
 * @param type Type of the attribute, e.g. GL_FLOAT_VEC3
 * @return Pointer to the bin for the attribute
 * @throw std::exception if name is empty
 * @throw std::exception if bin already exists and type is different
 * @throw std::exception if bin does not exist and allocating it fails
 */
MeshBuilder::AttributeBin* MeshBuilder::findBin(const string &name,
                                                GLenum type) {
    
    map<string,AttributeBin*>::iterator it;
    AttributeBin *bin = NULL;
    
    // Validate
    if (name.empty()) {
        throw Exception("[MeshBuilder] Name is empty!");
    }
    
    // Find or make the bin
    it = bins.find(name);
    if (it != bins.end()) {
        bin = it->second;
        if (bin->getType() != type) {
            throw Exception("[MeshBuilder] Attribute is not same type!");
        }
    } else {
        bin = new AttributeBin(name, type);
        if (bin == NULL) {
            throw Exception("[MeshBuilder] Could not allocate bin!");
        } else {
            bins[name] = bin;
        }
    }
    
    return bin;
}

/**
 * Checks if a type of geometry is supported.
 * 
 * @param type Type of geometry, e.g. GL_TRIANGLES
 * @return True if type is supported
 */
bool MeshBuilder::isSupportedType(GLenum type) {
    switch (type) {
    case GL_TRIANGLES: return true;
    default:
        return false;
    }
}

/* NESTED CLASSES */

MeshBuilder::Attribute::Attribute() {
    ;
}

MeshBuilder::Attribute::~Attribute() {
    ;
}

MeshBuilder::Vec2Attribute::Vec2Attribute(float x, float y) {
    this->x = x;
    this->y = y;
}

MeshBuilder::Vec2Attribute::~Vec2Attribute() {
    ;
}

void MeshBuilder::Vec2Attribute::putInto(VertexBuffer *vbo) {
    if (vbo == NULL) {
        throw Exception("[MeshBuilder] VertexBuffer is NULL!");
    } else {
        vbo->put(x, y);
    }
}

MeshBuilder::Vec3Attribute::Vec3Attribute(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

MeshBuilder::Vec3Attribute::~Vec3Attribute() {
    ;
}

void MeshBuilder::Vec3Attribute::putInto(VertexBuffer *vbo) {
    if (vbo == NULL) {
        throw Exception("[MeshBuilder] VertexBuffer is NULL!");
    } else {
        vbo->put(x, y, z);
    }
}

MeshBuilder::Vec4Attribute::Vec4Attribute(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

MeshBuilder::Vec4Attribute::~Vec4Attribute() {
    ;
}

void MeshBuilder::Vec4Attribute::putInto(VertexBuffer *vbo) {
    if (vbo == NULL) {
        throw Exception("[MeshBuilder] VertexBuffer is NULL!");
    } else {
        vbo->put(x, y, z, w);
    }
}

MeshBuilder::AttributeBin::AttributeBin(const string &name, GLenum type) {
    this->name = name;
    this->type = type;
}

MeshBuilder::AttributeBin::~AttributeBin() {
    
    vector<Attribute*>::iterator it = attributes.begin();
    
    while (it != attributes.end()) {
        delete (*it);
        ++it;
    }
}

void MeshBuilder::AttributeBin::add(Attribute *attribute) {
    if (attribute == NULL) {
        throw Exception("[MeshBuilder] Attribute is NULL!");
    } else {
        attributes.push_back(attribute);
    }
}

MeshBuilder::Attribute* MeshBuilder::AttributeBin::getAttribute(GLuint index) {
    return attributes[index];
}

GLenum MeshBuilder::AttributeBin::getType() const {
    return type;
}

size_t MeshBuilder::AttributeBin::getSize() const {
    return attributes.size();
}

/**
 * Constructs a basic mesh.
 * 
 * @param vbo Vertex buffer holding mesh's data
 * @param mode Type of geometry, e.g. GL_TRIANGLES
 * @throw std::exception if builder is NULL
 */
MeshBuilder::BasicMesh::BasicMesh(VertexBuffer *vbo, GLenum mode) {
    if (vbo == NULL) {
        throw Exception("[MeshBuilder] Vertex buffer is NULL!");
    } else {
        this->vbo = vbo;
        this->mode = mode;
    }
}

/**
 * Destroys the basic mesh.
 */
MeshBuilder::BasicMesh::~BasicMesh() {
    delete vbo;
}

/**
 * Activates the mesh.
 */
void MeshBuilder::BasicMesh::bind() {
    vbo->bind();
}

/**
 * Draws the mesh.
 */
void MeshBuilder::BasicMesh::draw() {
    glDrawArrays(mode, 0, vbo->getCapacity());
}

/**
 * Deactivates the mesh.
 */
void MeshBuilder::BasicMesh::unbind() {
    vbo->unbind();
}

/**
 * Checks if an attribute is stored in the mesh.
 * 
 * @param name Name of the attribute
 * @return <tt>true</tt> if attribute is in mesh
 */
bool MeshBuilder::BasicMesh::hasAttribute(const string &name) const {
    
    list<string> names = getAttributeNames();
    list<string>::const_iterator it;
    
    for (it=names.begin(); it!=names.end(); ++it) {
        if ((*it) == name) {
            return true;
        }
    }
    return false;
}

/**
 * Returns the names of all attributes in the mesh.
 */
list<string> MeshBuilder::BasicMesh::getAttributeNames() const {
    return vbo->getAttributeNames();
}

/**
 * Determines the position of an attribute in the mesh.
 * 
 * @param name Name of an attribute
 * @return Position of the attribute in the mesh
 * @throw std::exception if attribute is not in the mesh
 */
GLuint MeshBuilder::BasicMesh::getAttributeOffset(const string &name) const {
    return vbo->getAttributeOffset(name);
}

/**
 * Determines the number of components of an attribute in the mesh.
 * 
 * @param name Name of an attribute
 * @return Number of components of the attribute in the mesh
 * @throw std::exception if attribute is not in the mesh
 */
GLuint MeshBuilder::BasicMesh::getAttributeSize(const string &name) const {
    return vbo->getAttributeSize(name);
}

/**
 * Determines the primitive type of an attribute in the mesh.
 * 
 * @param name Name of an attribute
 * @return Primitive type of the attribute, e.g. GL_FLOAT
 * @throw std::exception if attribute is not in the mesh
 */
GLenum MeshBuilder::BasicMesh::getAttributeType(const string &name) const {
    return vbo->getAttributeType(name);
}

/**
 * Returns the size in bytes of a single vertex in the mesh.
 */
GLuint MeshBuilder::BasicMesh::getStride() const {
    return vbo->getStride();
}
