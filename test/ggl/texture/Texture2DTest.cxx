/*
 * Texture2DTest
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/texture/Texture2DTest.hxx"
using namespace std;
using namespace Ggl;

void Texture2DTestListener::onWindowOpen(const WindowEvent &e) {
    ;
}

void Texture2DTestListener::onWindowPaint(const WindowEvent &e) {
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Texture2DTest::test() {
    
    WindowFactory wf;
    Window *window = wf.createWindow();
    Texture2DTestListener listener;
    
    window->addWindowListener(&listener);
    Window::open(window);
}

GGL_TEST_SUITE
GGL_ADD_TEST(test)
GGL_RUN_TESTS
