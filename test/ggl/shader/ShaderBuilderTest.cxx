/*
 * ShaderBuilderTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/common.h"
#include "ggl/shader/ShaderBuilder.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
using namespace std;
using namespace Ggl;


/**
 * 
 */
class ShaderBuilderTestListener : public WindowListener {
public:
    virtual void onWindowOpen(const WindowEvent &e);
    virtual void onWindowPaint(const WindowEvent &e);
    virtual void onWindowKey(const WindowEvent &e);
    virtual void onWindowClose(const WindowEvent &e);
};

void ShaderBuilderTestListener::onWindowOpen(const WindowEvent &e) {
    
    int handle;
    GLint result;
    GLchar buffer[1024];
    GLsizei length;
    stringstream stream;
    string line;
    vector<string> lines;
    
    // Compile
    handle = ShaderBuilder::build("test/ggl/shader/ShaderBuilderTest.vert");
    assert(handle > 0);
    glGetShaderiv(handle, GL_SHADER_TYPE, &result);
    assert(result == GL_VERTEX_SHADER);
    glGetShaderiv(handle, GL_COMPILE_STATUS, &result);
    assert(result == GL_TRUE);
    
    // Get the source
    glGetShaderSource(handle, 1024, &length, buffer);
    stream << buffer;
    getline(stream, line);
    lines.push_back(line);
    while (stream) {
        getline(stream, line);
        lines.push_back(line);
    }
    
    // Check the source
    assert(lines[0] == "#version 330");
    assert(lines[1] == "uniform mat4 MVPMatrix = mat4(1.0);");
    assert(lines[2] == "in vec4 MCVertex;");
    assert(lines[3] == "void main() {");
    assert(lines[4] == "    gl_Position = MVPMatrix * MCVertex;");
    assert(lines[5] == "}");
}

void ShaderBuilderTestListener::onWindowPaint(const WindowEvent &e) {
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ShaderBuilderTestListener::onWindowKey(const WindowEvent &e) {
    if (e.getTrigger() == GGL_KEY_ESCAPE) {
        e.getWindow()->close();
    }
}

void ShaderBuilderTestListener::onWindowClose(const WindowEvent &e) {
    cout << "PASSED" << endl;
}


/**
 * Unit test for ShaderBuilder.
 */
class ShaderBuilderTest : public TestFixture {
public:
    void testBuild();
};

/**
 * Ensures a shader can be built properly from a file.
 */
void ShaderBuilderTest::testBuild() {
    
    WindowFactory factory;
    Ggl::Window *window = factory.createWindow();
    ShaderBuilderTestListener listener;
    
    window->addWindowListener(&listener);
    Ggl::Window::open(window);
}

/* Run the test. */
#define GGL_TEST_FIXTURE ShaderBuilderTest
GGL_TEST_SUITE
GGL_ADD_TEST(testBuild)
GGL_RUN_TESTS
