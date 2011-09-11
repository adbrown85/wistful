/*
 * ModelBuilderTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/geometry/ModelBuilderTest.hxx"
using namespace std;
using namespace Ggl;

/**
 * Ensures ModelBuilder works correctly.
 */
void ModelBuilderTest::test() {
    
    WindowFactory factory;
    Ggl::Window *window = factory.createWindow();
    WindowObserver observer;
    
    window->addWindowListener(&observer);
    Ggl::Window::open(window);
}

ModelBuilderTest::WindowObserver::WindowObserver() {
    this->program = 0;
    this->mesh = NULL;
    this->model = NULL;
}

ModelBuilderTest::WindowObserver::~WindowObserver() {
    ;
}

void ModelBuilderTest::WindowObserver::onWindowOpen(const WindowEvent &e) {
    program = createProgram();
    mesh = createMesh();
    model = createModel(mesh, program);
}

void ModelBuilderTest::WindowObserver::onWindowPaint(const WindowEvent &e) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    model->render();
}

void ModelBuilderTest::WindowObserver::onWindowClose(const WindowEvent &e) {
    glDeleteProgram(program);
    delete mesh;
    delete model;
    program = 0;
    mesh = NULL;
    model = NULL;
}

// HELPERS

GLuint ModelBuilderTest::WindowObserver::createProgram() {
    
    ProgramBuilder pb;
    
    pb.addShader("test/ggl/geometry/coordinates.vert");
    pb.addShader("test/ggl/geometry/coordinates.frag");
    return pb.toProgram();
}

Mesh* ModelBuilderTest::WindowObserver::createMesh() {
    
    MeshBuilder mb(GL_TRIANGLES);
    
    // First triangle
    mb.add("MCVertex", +0.5f, +0.5f, 0.0f);
    mb.add("TexCoord0", 1.0f, 1.0f, 0.0f);
    mb.add("MCVertex", -0.5f, +0.5f, 0.0f);
    mb.add("TexCoord0", 0.0f, 1.0f, 0.0f);
    mb.add("MCVertex", -0.5f, -0.5f, 0.0f);
    mb.add("TexCoord0", 0.0f, 0.0f, 0.0f);
    
    // Second triangle
    mb.add("MCVertex", -0.5f, -0.5f, 0.0f);
    mb.add("TexCoord0", 0.0f, 0.0f, 0.0f);
    mb.add("MCVertex", +0.5f, -0.5f, 0.0f);
    mb.add("TexCoord0", 1.0f, 0.0f, 0.0f);
    mb.add("MCVertex", +0.5f, +0.5f, 0.0f);
    mb.add("TexCoord0", 1.0f, 1.0f, 0.0f);
    
    return mb.toMesh();
}

Model* ModelBuilderTest::WindowObserver::createModel(Mesh *m, GLuint p) {
    
    ModelBuilder mb;
    
    mb.setMesh(m);
    mb.setProgram(p);
    return mb.toModel();
}

// MAIN

#define GGL_TEST_FIXTURE ModelBuilderTest
GGL_TEST_SUITE
GGL_ADD_TEST(test)
GGL_RUN_TESTS
