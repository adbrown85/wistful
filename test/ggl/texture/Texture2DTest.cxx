/*
 * Texture2DTest
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/texture/Texture2DTest.hxx"
using namespace std;
using namespace Ggl;

void Texture2DTest::test() {
    
    WindowFactory wf;
    Window *window = wf.createWindow();
    Texture2DTestListener listener;
    
    window->addWindowListener(&listener);
    Window::open(window);
}

void Texture2DTestListener::onWindowOpen(const WindowEvent &e) {
    vbo = createVBO();
    program = createProgram();
    vao = createVAO(vbo, program);
}

void Texture2DTestListener::onWindowPaint(const WindowEvent &e) {
    
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(program);
    glBindVertexArray(vao);
    
    glDrawArrays(
            GL_TRIANGLES, // mode
            0,            // first
            3);           // count
}

//----------------------------------------
// Helpers
//

GLuint Texture2DTestListener::createVAO(VertexBuffer *vbo,
                                        GLuint program) {
    
    GLuint vao;
    int loc = glGetAttribLocation(program, "MCVertex");
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    vbo->bind();
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(
            loc,
            2,
            GL_FLOAT,
            GL_FALSE,
            vbo->getStride(),
            (GLvoid*) vbo->getOffset("MCVertex"));
    
    return vao;
}

VertexBuffer* Texture2DTestListener::createVBO() {
    
    VertexBufferBuilder vbb;
    VertexBuffer *vb;
    
    vbb.addAttribute("MCVertex", 2);
    vbb.setCapacity(3);
    vbb.setUsage(GL_STATIC_DRAW);
    vb = vbb.toVertexBuffer();
    
    vb->bind();
    vb->put(+0.5, +0.5);
    vb->put(-0.5, +0.5);
    vb->put(-0.5, -0.5);
    vb->flush();
    
    return vb;
}

GLuint Texture2DTestListener::createProgram() {
    
    GLuint vs = loadShader("Texture2DTest.vert");
    GLuint fs = loadShader("Texture2DTest.frag");
    
    return ProgramBuilder::build(vs, fs);
}

GLuint Texture2DTestListener::loadShader(const string &filename) {
    
    ostringstream ss;
    
    ss << "test/ggl/texture" << '/' << filename;
    return ShaderBuilder::build(ss.str());
}

//----------------------------------------
// Main
//

GGL_TEST_SUITE
GGL_ADD_TEST(test)
GGL_RUN_TESTS
