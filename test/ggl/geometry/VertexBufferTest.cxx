/*
 * VertexBufferTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "ggl/geometry/VertexBufferTest.hxx"
using namespace std;
using namespace Edo;
using namespace Ggl;

void VertexBufferTest::run() {
    
    WindowFactory factory;
    Ggl::Window *window = factory.createWindow();
    VertexBufferTestListener listener;
    
    window->addWindowListener(&listener);
    Ggl::Window::open(window);
}

VertexBufferTestListener::VertexBufferTestListener() {
    vbo = NULL;
    program = 0;
    pointLoc = -1;
}

void VertexBufferTestListener::onWindowOpen(const WindowEvent &e) {
    
    VertexBufferBuilder builder;
    
    builder.addAttribute("MCVertex", GL_FLOAT_VEC3);
    builder.addAttribute("TexCoord0", GL_FLOAT_VEC3);
    builder.setUsage(GL_STATIC_DRAW);
    builder.setCapacity(3);
    
    vbo = builder.toVertexBuffer();
    vbo->bind();
    vbo->put(-0.5, +0.5, 0); // 1
    vbo->put( 0.0,  1.0, 0);
    vbo->put(-0.5, -0.5, 0); // 2
    vbo->put( 0.0,  0.0, 0);
    vbo->put(+0.5, +0.5, 0); // 3
    vbo->put( 1.0,  1.0, 0);
    vbo->flush();
    vbo->unbind();
    
    program = createProgram();
    
    pointLoc = glGetAttribLocation(program, "MCVertex");
    if (pointLoc < 0) {
        throw Exception("Location of MCVertex not found!");
    }
    
    glViewport(0, 0, 512, 512);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    vbo->bind();
    glVertexAttribPointer(
            pointLoc,         // index
            3,                // size
            GL_FLOAT,         // type
            GL_FALSE,         // normalized
            vbo->getStride(),            // stride
            (GLvoid*) vbo->getAttributeOffset("MCVertex")); // offset
    glEnableVertexAttribArray(pointLoc);
    vbo->unbind();
    glBindVertexArray(0);
    
    glBindFragDataLocation(program, 0, "FragColor");
}

void VertexBufferTestListener::onWindowPaint(const WindowEvent &e) {
    
    glClearColor(0, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(program);
    
    glBindVertexArray(vao);
    glDrawArrays(
            GL_TRIANGLES, // mode
            0,            // first
            3);           // count
    glBindVertexArray(0);
}

void VertexBufferTestListener::onWindowKey(const WindowEvent &event) {
    if (event.getTrigger() == GGL_KEY_ESCAPE) {
        event.getWindow()->close();
    }
}

void VertexBufferTestListener::onWindowClose(const WindowEvent &e) {
    if (vbo != NULL) {
        delete vbo;
    }
}

//----------------------------------------
// Helpers
//

GLuint VertexBufferTestListener::createProgram() {
    
    ProgramBuilder pb;
    
    pb.addShader("test/ggl/geometry/VertexBufferTest.vert");
    pb.addShader("test/ggl/geometry/VertexBufferTest.frag");
    return pb.toProgram();
}

int main(int argc, char *argv[]) {

    VertexBufferTest test;

    test.run();
    return 0;
}
