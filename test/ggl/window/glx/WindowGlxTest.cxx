/*
 * WindowGlxTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/WindowFactory.hpp"
#include <iostream>
using namespace std;
namespace Ggl {

/** Test for GlWindowGlx. */
class WindowGlxTest {
public:
    void testOpen();
};

class FakeWindowListener : public WindowListener {
public:
    virtual void onInit(Window *window) {
        cerr << "FakeGglListener::init()" << endl;
    }
    virtual void onDisplay(Window *window) {
        cerr << "FakeGglListener::display()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void onDestroy(Window *window) {
        cerr << "FakeGglListener::destroy()" << endl;
    }
    virtual void onKey(Window *window, WindowEvent &event) {
        switch (event.getTrigger()) {
        case GGL_ESCAPE:
            cerr << "GGL_ESCAPE" << endl;
            window->close();
            break;
        case GGL_A:
            cerr << "GGL_A" << endl;
            break;
        case GGL_a:
            cerr << "GGL_a" << endl;
            break;
        }
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