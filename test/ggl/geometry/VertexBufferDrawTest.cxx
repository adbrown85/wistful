/*
 * VertexBufferObjectDrawTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/common.h"
#include "ggl/geometry/VertexBuffer.hpp"
#include "ggl/geometry/VertexBufferBuilder.hpp"
#include "ggl/shader/ShaderBuilder.hpp"
#include "ggl/shader/ProgramBuilder.hpp"
#include "ggl/system/ErrorChecker.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
using namespace std;
using namespace Ggl;


/**
 * 
 */
class VertexBufferTestWindowListener : public WindowListener {
public:
    VertexBufferTestWindowListener();
    virtual void onInit(const WindowEvent&);
    virtual void onDisplay(const WindowEvent&);
    virtual void onDestroy(const WindowEvent&);
    virtual void onKey(const WindowEvent &event);
private:
    VertexBuffer *vbo;
    GLuint program;
    GLint pointLoc;
    GLuint vao;
};

VertexBufferTestWindowListener::VertexBufferTestWindowListener() {
    vbo = NULL;
    program = 0;
    pointLoc = -1;
}

void VertexBufferTestWindowListener::onInit(const WindowEvent &e) {
    
    GLuint vertShader, fragShader;
    VertexBufferBuilder builder;
    
    builder.addAttribute("MCVertex", 3);
    builder.addAttribute("TexCoord0", 3);
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
    
    vertShader = ShaderBuilder::build("test/ggl/geometry/VertexBufferTest.vert");
    fragShader = ShaderBuilder::build("test/ggl/geometry/VertexBufferTest.frag");
    program = ProgramBuilder::build(vertShader, fragShader);
    
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
            (GLvoid*) vbo->getOffset("MCVertex")); // offset
    glEnableVertexAttribArray(pointLoc);
    vbo->unbind();
    glBindVertexArray(0);
    
    glBindFragDataLocation(program, 0, "FragColor");
}

void VertexBufferTestWindowListener::onDisplay(const WindowEvent &e) {
    
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

void VertexBufferTestWindowListener::onDestroy(const WindowEvent &e) {
    if (vbo != NULL) {
        delete vbo;
    }
}

void VertexBufferTestWindowListener::onKey(const WindowEvent &event) {
    if (event.getTrigger() == GGL_KEY_ESCAPE) {
        event.getWindow()->close();
    }
}


class VertexBufferDrawTest : public TestFixture {
public:
    void testDraw();
};

void VertexBufferDrawTest::testDraw() {
    
    WindowFactory factory;
    Ggl::Window *window = factory.createWindow();
    
    window->addWindowListener(new VertexBufferTestWindowListener());
    Ggl::Window::open(window);
}

#define GGL_TEST_FIXTURE VertexBufferDrawTest
GGL_TEST_SUITE
GGL_ADD_TEST(testDraw)
GGL_RUN_TESTS
