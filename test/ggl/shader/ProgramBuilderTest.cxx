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


class ProgramBuilderTestWindowListener : public WindowListener {
    virtual void onInit(Ggl::Window *window);
    virtual void onDisplay(Ggl::Window *window);
    virtual void onDestroy(Ggl::Window *window);
    virtual void onKey(Ggl::Window *window, const WindowEvent &event);
};

void ProgramBuilderTestWindowListener::onInit(Ggl::Window *window) {
    
    list<GLuint> shaders;
    GLuint program, shader;
    
    shader = ShaderBuilder::build("test/ggl/shader/ProgramBuilderTest.frag");
    shaders.push_back(shader);
    shader = ShaderBuilder::build("test/ggl/shader/ProgramBuilderTest.vert");
    shaders.push_back(shader);
    
    program = ProgramBuilder::build(shaders);
    assert(program > 0);
}

void ProgramBuilderTestWindowListener::onDisplay(Ggl::Window *window) {
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ProgramBuilderTestWindowListener::onDestroy(Ggl::Window *window) {
    cout << "PASSED" << endl;
}

void ProgramBuilderTestWindowListener::onKey(Ggl::Window *window,
                                             const WindowEvent &event) {
    if (event.getTrigger() == GGL_KEY_ESCAPE) {
        window->close();
    }
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
    
    window->addWindowListener(new ProgramBuilderTestWindowListener());
    Ggl::Window::open(window);
}

/* Run the test. */
#define GGL_TEST_FIXTURE ProgramBuilderTest
GGL_TEST_SUITE
GGL_ADD_TEST(testBuild)
GGL_RUN_TESTS

