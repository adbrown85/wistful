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
    Ggl::Window *window = wf.createWindow();
    Texture2DTestListener listener;
    
    window->addWindowListener(&listener);
    Ggl::Window::open(window);
}

void Texture2DTestListener::onWindowOpen(const WindowEvent &e) {
    vbo = createVBO();
    program = createProgram();
    vao = createVAO(vbo, program);
    texture = createTexture();
}

void Texture2DTestListener::onWindowPaint(const WindowEvent &e) {
    
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(program);
    glBindVertexArray(vao);
    texture->bind();
    
    glDrawArrays(
            GL_TRIANGLES, // mode
            0,            // first
            6);           // count
}

void Texture2DTestListener::onWindowClose(const WindowEvent &e) {
    delete texture;
}

//----------------------------------------
// Helpers
//

Image* Texture2DTestListener::createImage() {
    
    BitmapReader reader;
    
    reader.read("test/ggl/texture/crate.bmp");
    return reader.toImage();
}

GLuint Texture2DTestListener::createVAO(VertexBuffer *vbo,
                                        GLuint program) {
    
    GLuint vao;
    int loc;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    vbo->bind();
    
    loc = glGetAttribLocation(program, "MCVertex");
    assert(loc != -1);
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(
            loc,
            2,
            GL_FLOAT,
            GL_FALSE,
            vbo->getStride(),
            (GLvoid*) vbo->getOffset("MCVertex"));
    
    loc = glGetAttribLocation(program, "TexCoord0");
    assert(loc != -1);
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(
            loc,
            2,
            GL_FLOAT,
            GL_FALSE,
            vbo->getStride(),
            (GLvoid*) vbo->getOffset("TexCoord0"));
    
    return vao;
}

VertexBuffer* Texture2DTestListener::createVBO() {
    
    VertexBufferBuilder vbb;
    VertexBuffer *vb;
    
    vbb.addAttribute("MCVertex", 2);
    vbb.addAttribute("TexCoord0", 2);
    vbb.setCapacity(6);
    vbb.setUsage(GL_STATIC_DRAW);
    vb = vbb.toVertexBuffer();
    
    vb->bind();
    vb->put(+0.5, +0.5);
    vb->put( 1.0,  1.0);
    vb->put(-0.5, +0.5);
    vb->put( 0.0,  1.0);
    vb->put(-0.5, -0.5);
    vb->put( 0.0,  0.0);
    vb->put(-0.5, -0.5);
    vb->put( 0.0,  0.0);
    vb->put(+0.5, -0.5);
    vb->put( 1.0,  0.0);
    vb->put(+0.5, +0.5);
    vb->put( 1.0,  1.0);
    vb->flush();
    
    assert(vb->getStride() == 16);
    assert(vb->getOffset("MCVertex") == 0);
    assert(vb->getOffset("TexCoord0") == 8);
    
    return vb;
}

GLuint Texture2DTestListener::createProgram() {
    
    GLuint vs = loadShader("Texture2DTest.vert");
    GLuint fs = loadShader("Texture2DTest.frag");
    
    return ProgramBuilder::build(vs, fs);
}

Texture* Texture2DTestListener::createTexture() {
    
    Texture2D *texture = Texture2D::newInstance();
    Image *image = createImage();
    size_t len = image->getSize();
    size_t width = image->getWidth();
    size_t height = image->getHeight();
    
    assert(len == 196610);
    assert(width == 256);
    assert(height == 256);
    
    texture->bind();
    texture->allocate(GL_RGB, Dimension(width, height, 1));
    texture->load(*image);
    
    delete image;
    return texture;
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
