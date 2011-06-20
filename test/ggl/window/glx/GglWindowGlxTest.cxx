/*
 * GglWindowGlxTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/GglWindowFactory.hpp"
#include <iostream>
using namespace std;

/** Test for GlWindowGlx. */
class GglWindowGlxTest {
public:
    void testOpen();
};

class FakeWindowListener : public Ggl::WindowListener {
public:
    virtual void onInit(Ggl::Window *window) {
        cerr << "FakeGglListener::init()" << endl;
    }
    virtual void onDisplay(Ggl::Window *window) {
        cerr << "FakeGglListener::display()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void onDestroy(Ggl::Window *window) {
        cerr << "FakeGglListener::destroy()" << endl;
    }
    virtual void onKey(Ggl::Window *window, Ggl::WindowEvent &event) {
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
void GglWindowGlxTest::testOpen() {
    
    Ggl::WindowFactory factory;
    Ggl::Window *window = factory.createWindow();
    
    window->setLocation(50, 50);
    window->setSize(640, 480);
    window->addWindowListener(new FakeWindowListener());
    Ggl::Window::open(window);
    
    cerr << "End of GglWindowGlxTest::testOpen()" << endl;
}

/** Runs the test. */
int main(int argc, char *argv[]) {
    GglWindowGlxTest test;
    
    test.testOpen();
}
