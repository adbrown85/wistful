/*
 * ModelBuilder.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/geometry/ModelBuilder.hpp"
using namespace Ggl;
using namespace std;

/**
 * Constructs a model builder.
 */
ModelBuilder::ModelBuilder() {
    this->mesh = NULL;
    this->program = -1;
}

/**
 * Destroys a model builder.
 */
ModelBuilder::~ModelBuilder() {
    ;
}

/**
 * Changes the mesh that will be used to make the model.
 * 
 * @param mesh Mesh used to make the model
 * @throw std::exception if mesh is NULL
 */
void ModelBuilder::setMesh(Mesh *mesh) {
    if (mesh == NULL) {
        throw Exception("[ModelBuilder] Mesh is NULL!");
    } else {
        this->mesh = mesh;
    }
}

/**
 * Changes the shader program that will be used to make the model.
 * 
 * @param program Program used to make the model
 * @throw std::exception if program is not a shader program
 */
void ModelBuilder::setProgram(GLuint program) {
    if (!glIsProgram(program)) {
        throw Exception("[ModelBuilder] Program is not a program!");
    } else {
        this->program = program;
    }
}

/**
 * Finishes building the model.
 * 
 * @return Pointer to a new model, which should be deleted when done with
 * @throw std::exception if mesh was not set
 * @throw std::exception if program was not set
 */
Model* ModelBuilder::toModel() {
    
    // Validate
    if (mesh == NULL) {
        throw Exception("[ModelBuilder] Mesh was not set!");
    } else if (program == -1) {
        throw Exception("[ModelBuilder] Program was not set!");
    }
    
    return new BasicModel(mesh, program);
}

// HELPERS

/**
 * Creates a Vertex Array Object tying a mesh and a program together.
 * 
 * @param mesh Mesh holding vertex attribute values
 * @param program Shader program accepting vertex attributes
 * @return New Vertex Array Object tying mesh and program together
 */
GLuint ModelBuilder::createVAO(Mesh *mesh, GLuint program) {
    
    GLuint vao = generateVAO();
    list<string> attributes = findAttributes(program);
    list<string>::iterator it;
    
    // Bind
    glBindVertexArray(vao);
    mesh->bind();
    
    // Enable attributes
    for (it=attributes.begin(); it!=attributes.end(); ++it) {
        if (mesh->hasAttribute(*it)) {
            enable(mesh, program, *it);
        }
    }
    
    // Unbind
    mesh->unbind();
    glBindVertexArray(0);
    
    return vao;
}

/**
 * Enables a vertex attribute.
 * 
 * @param mesh Mesh holding vertex attribute values
 * @param program Shader program accepting vertex attributes
 * @param name Name of a vertex attribute
 */
void ModelBuilder::enable(Mesh *mesh, GLuint program, const string &name) {
    
    GLint location = glGetAttribLocation(program, name.c_str());
    GLint size = mesh->getAttributeSize(name);
    GLenum type = mesh->getAttributeType(name);
    GLsizei stride = mesh->getStride();
    const GLvoid* offset = (const GLvoid*) mesh->getAttributeOffset(name);
    
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, size, type, false, stride, offset);
}

/**
 * Determines all the vertex attributes in a shader program.
 * 
 * @param program Shader program to check
 * @return List of vertex attributes in program
 */
list<string> ModelBuilder::findAttributes(GLuint program) {
    
    list<string> attributes;
    GLint number;
    GLint size;
    GLenum type;
    GLchar name[128];
    
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &number);
    for (int i=0; i<number; ++i) {
        glGetActiveAttrib(
                program,  // program
                i,        // index
                128,      // bufSize
                NULL,     // length
                &size,    // size
                &type,    // type
                name);    // name
        attributes.push_back(name);
    }
    
    return attributes;
}

/**
 * Returns a handle to a new Vertex Array Object.
 */
GLuint ModelBuilder::generateVAO() {
    
    GLuint handle;
    
    glGenVertexArrays(1, &handle);
    return handle;
}

// NESTED CLASSES

/**
 * Constructs a basic model.
 * 
 * @param mesh Mesh to use for model (assumed not NULL)
 * @param program Program to use for model (assumed valid program)
 */
ModelBuilder::BasicModel::BasicModel(Mesh *mesh, GLuint program) {
    this->mesh = mesh;
    this->program = program;
    this->vao = createVAO(mesh, program);
}

/**
 * Destroys a basic model.
 */
ModelBuilder::BasicModel::~BasicModel() {
    
    GLuint handles[1];
    
    handles[0] = vao;
    glDeleteVertexArrays(1, handles);
}

/**
 * Renders the model.
 */
void ModelBuilder::BasicModel::render() {
    glUseProgram(program);
    glBindVertexArray(vao);
    mesh->draw();
}
