/*
 * ModelBuilder.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MODELBUILDER_HPP
#define GGL_MODELBUILDER_HPP
#include "ggl/common.h"
#include "ggl/geometry/Mesh.hpp"
#include "ggl/geometry/Model.hpp"
namespace Ggl {


/**
 * Utility for building a model.
 * 
 * @ingroup geometry
 */
class ModelBuilder {
public:
    ModelBuilder();
    virtual ~ModelBuilder();
    virtual void setMesh(Mesh *mesh);
    virtual void setProgram(GLuint program);
    virtual Model* toModel();
private:
// Instance variables
    Mesh *mesh;
    GLuint program;
// Nested classes
    class BasicModel;
// Helpers
    static GLuint createVAO(Mesh *mesh, GLuint program);
    static void enable(Mesh *mesh, GLuint program, const std::string &name);
    static std::list<std::string> findAttributes(GLuint program);
    static GLuint generateVAO();
// Constructors
    ModelBuilder(const ModelBuilder&);
    ModelBuilder& operator=(const ModelBuilder&);
};


/**
 * Simple implementation of a model.
 */
class ModelBuilder::BasicModel : public Model {
public:
    BasicModel(Mesh *mesh, GLuint program);
    virtual ~BasicModel();
    virtual void render();
private:
// Instance variables
    Mesh *mesh;
    GLuint program;
    GLuint vao;
// Constructors
    BasicModel(const BasicModel&);
    BasicModel& operator=(const BasicModel&);
};

} /* namespace Ggl */
#endif
