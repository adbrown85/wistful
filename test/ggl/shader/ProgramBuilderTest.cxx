/*
 * ProgramBuilderTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/shader/ProgramBuilderTest.hxx"
using namespace std;
using namespace Ggl;

void ProgramBuilderTestListener::onWindowOpen(const WindowEvent &e) {
    
    GLuint program;
    ProgramBuilder pb;
    
    pb.addShader("test/ggl/shader/ProgramBuilderTest.frag");
    pb.addShader("test/ggl/shader/ProgramBuilderTest.vert");
    
    program = pb.toProgram();
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

void ProgramBuilderTest::testBuild() {
	
    WindowFactory factory;
    Ggl::Window *window = factory.createWindow();
    
    window->addWindowListener(new ProgramBuilderTestListener());
    Ggl::Window::open(window);
}

GGL_TEST_SUITE
GGL_ADD_TEST(testBuild)
GGL_RUN_TESTS

