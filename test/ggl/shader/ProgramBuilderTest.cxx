/*
 * ProgramBuilderTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/common.h"
#include "ggl/shader/ProgramBuilder.hpp"
#include "ggl/shader/ShaderBuilder.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
using namespace std;
using namespace Ggl;


class ProgramBuilderTestListener : public WindowListener {
    virtual void onWindowOpen(const WindowEvent &e);
    virtual void onWindowPaint(const WindowEvent &e);
    virtual void onWindowKey(const WindowEvent &e);
    virtual void onWindowClose(const WindowEvent &e);
};

void ProgramBuilderTestListener::onWindowOpen(const WindowEvent &e) {
    
    list<GLuint> shaders;
    GLuint program, shader;
    
    shader = ShaderBuilder::build("test/ggl/shader/ProgramBuilderTest.frag");
    shaders.push_back(shader);
    shader = ShaderBuilder::build("test/ggl/shader/ProgramBuilderTest.vert");
    shaders.push_back(shader);
    
    program = ProgramBuilder::build(shaders);
    assert(program > 0);
}

void ProgramBuilderTestListener::onWindowPaint(const WindowEvent &e) {
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ProgramBuilderTestListener::onWindowKey(const WindowEvent &e) {
    if (e.getTrigger() == GGL_KEY_ESCAPE) {
        e.getWindow()->close();
    }
}

void ProgramBuilderTestListener::onWindowClose(const WindowEvent &e) {
    cout << "PASSED" << endl;
}


/**
 * @brief Unit test for ProgramBuilder.
 */
class ProgramBuilderTest : public TestFixture {
public:
    void testBuild();
};

/**
 * Ensures a program can be linked.
 */
void ProgramBuilderTest::testBuild() {
	
    WindowFactory factory;
    Ggl::Window *window = factory.createWindow();
    
    window->addWindowListener(new ProgramBuilderTestListener());
    Ggl::Window::open(window);
}

/* Run the test. */
#define GGL_TEST_FIXTURE ProgramBuilderTest
GGL_TEST_SUITE
GGL_ADD_TEST(testBuild)
GGL_RUN_TESTS

