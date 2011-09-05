/*
 * MeshBuilderTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/geometry/MeshBuilderTest.hxx"
using namespace std;
using namespace Ggl;

/**
 * Runs the test.
 */
void MeshBuilderTest::test() {
    
    WindowFactory factory;
    Ggl::Window *window = factory.createWindow();
    WindowObserver observer;
    
    window->addWindowListener(&observer);
    Ggl::Window::open(window);
}

/**
 * Constructs a window observer.
 */
MeshBuilderTest::WindowObserver::WindowObserver() {
    this->mesh = NULL;
    this->program = 0;
    this->vao = 0;
}

/**
 * Destroys a window observer.
 */
MeshBuilderTest::WindowObserver::~WindowObserver() {
    if (mesh != NULL) {
        delete mesh;
    }
}

void MeshBuilderTest::WindowObserver::onWindowOpen(const WindowEvent &we) {
    try {
        mesh = createMesh();
        program = createProgram();
        vao = createVAO(mesh, program);
    } catch (std::exception &e) {
        cout << e.what() << endl;
    }
    ErrorChecker::checkErrors("End of onWindowOpen()");
}

void MeshBuilderTest::WindowObserver::onWindowPaint(const WindowEvent &we) {
    
    // Clear
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw
    glUseProgram(program);
    glBindVertexArray(vao);
    mesh->bind();
    mesh->draw();
    ErrorChecker::checkErrors("End of onWindowPaint()");
}

void MeshBuilderTest::WindowObserver::onWindowKey(const WindowEvent &we) {
    ;
}

void MeshBuilderTest::WindowObserver::onWindowClose(const WindowEvent &we) {
    ;
}

/* HELPERS */

Mesh* MeshBuilderTest::WindowObserver::createMesh() {
    
    MeshBuilder mb(GL_TRIANGLES);
    
    mb.add("MCVertex", +0.5f, +0.5f, 0.0);
    mb.add("TexCoord0", 1.0f, 1.0f, 0.0);
    mb.add("MCVertex", -0.5f, +0.5f, 0.0);
    mb.add("TexCoord0", 0.0f, 1.0f, 0.0);
    mb.add("MCVertex", -0.5f, -0.5f, 0.0);
    mb.add("TexCoord0", 0.0f, 0.0f, 0.0);
    mb.add("MCVertex", -0.5f, -0.5f, 0.0);
    mb.add("TexCoord0", 0.0f, 0.0f, 0.0);
    mb.add("MCVertex", +0.5f, -0.5f, 0.0);
    mb.add("TexCoord0", 1.0f, 0.0f, 0.0);
    mb.add("MCVertex", +0.5f, +0.5f, 0.0);
    mb.add("TexCoord0", 1.0f, 1.0f, 0.0);
    
    return mb.toMesh();
}

GLuint MeshBuilderTest::WindowObserver::createProgram() {
    
    ProgramBuilder pb;
    
    pb.addShader("test/ggl/geometry/coordinates.vert");
    pb.addShader("test/ggl/geometry/coordinates.frag");
    return pb.toProgram();
}

GLuint MeshBuilderTest::WindowObserver::createVAO(Mesh *mesh, GLuint program) {
    
    GLuint handle;
    GLint location;
    
    // Generate
    glGenVertexArrays(1, &handle);
    
    // Bind
    glBindVertexArray(handle);
    mesh->bind();
    
    // Set up MCVertex attribute
    location = glGetAttribLocation(program, "MCVertex");
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(
            location,
            mesh->getSize("MCVertex"),
            mesh->getType("MCVertex"),
            false,
            mesh->getStride(),
            (GLvoid*) mesh->getOffset("MCVertex"));
    
    // Set up TexCoord0 attribute
    location = glGetAttribLocation(program, "TexCoord0");
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(
            location,
            mesh->getSize("TexCoord0"),
            mesh->getType("TexCoord0"),
            false,
            mesh->getStride(),
            (GLvoid*) mesh->getOffset("TexCoord0"));
    
    // Unbind
    mesh->unbind();
    glBindVertexArray(0);
    
    return handle;
}

/* MAIN */

#define GGL_TEST_FIXTURE MeshBuilderTest
GGL_TEST_SUITE
GGL_ADD_TEST(test)
GGL_RUN_TESTS
