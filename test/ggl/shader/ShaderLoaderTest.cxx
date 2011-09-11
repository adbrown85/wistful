/*
 * ShaderLoaderTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/shader/ShaderLoaderTest.hxx"
using namespace std;
using namespace Edo;
using namespace Ggl;

void ShaderLoaderTestListener::onWindowOpen(const WindowEvent &e) {
    
    int handle;
    GLint result;
    GLchar buffer[1024];
    GLsizei length;
    stringstream stream;
    string line;
    vector<string> lines;
    
    // Compile
    handle = ShaderLoader::load("test/ggl/shader/ShaderLoaderTest.vert");
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

void ShaderLoaderTestListener::onWindowPaint(const WindowEvent &e) {
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ShaderLoaderTestListener::onWindowKey(const WindowEvent &e) {
    if (e.getTrigger() == GGL_KEY_ESCAPE) {
        e.getWindow()->close();
    }
}

void ShaderLoaderTestListener::onWindowClose(const WindowEvent &e) {
    cout << "PASSED" << endl;
}

/**
 * Ensures a shader can be loaded properly from a file.
 */
void ShaderLoaderTest::run() {
    
    WindowFactory factory;
    Ggl::Window *window = factory.createWindow();
    ShaderLoaderTestListener listener;
    
    window->addWindowListener(&listener);
    Ggl::Window::open(window);
}

/* Run the test. */
int main(int argc, char *argv[]) {

    ShaderLoaderTest test;

    test.run();
    return 0;
}
