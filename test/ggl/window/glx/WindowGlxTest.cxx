/*
 * WindowGlxTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "ggl/window/WindowFactory.hpp"
#include <iostream>
using namespace std;
namespace Ggl {

/**
 * Test for GlWindowGlx.
 */
class WindowGlxTest {
public:
    void testOpen();
};

class FakeWindowListener : public WindowListener {
public:
    virtual void onWindowOpen(const WindowEvent &e) {
        cerr << "FakeGglListener::onWindowOpen()" << endl;
    }
    virtual void onWindowPaint(const WindowEvent &e) {
        cerr << "FakeGglListener::onWindowPaint()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void onWindowKey(const WindowEvent &e) {
        switch (e.getTrigger()) {
        case GGL_KEY_ESCAPE:
            cerr << "GGL_KEY_ESCAPE" << endl;
            e.getWindow()->close();
            break;
        case GGL_KEY_A:
            cerr << "GGL_KEY_A" << endl;
            break;
        case GGL_KEY_a:
            cerr << "GGL_KEY_a" << endl;
            break;
        }
    }
    virtual void onWindowClose(const WindowEvent &e) {
        cerr << "FakeGglListener::onWindowClose()" << endl;
    }
};

/** Ensures window can be opened. */
void Ggl::WindowGlxTest::testOpen() {
    
    WindowFactory factory;
    Window *window = factory.createWindow();
    
    window->setLocation(50, 50);
    window->setSize(640, 480);
    window->addWindowListener(new FakeWindowListener());
    Window::open(window);
    
    cerr << "End of Ggl::WindowGlxTest::testOpen()" << endl;
}

} // End of namespace Ggl

/** Runs the test. */
int main(int argc, char *argv[]) {
    
    Ggl::WindowGlxTest test;
    
    test.testOpen();
}
