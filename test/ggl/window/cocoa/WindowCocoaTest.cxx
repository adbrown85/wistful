/*
 * WindowCocoaTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/WindowFactory.hpp"
using namespace std;
namespace Ggl {

/**
 * Test for GglWindowCoca.
 */
class WindowCocoaTest {
public:
    void testOpen();
};

class FakeWindowListener : public WindowListener {
public:
    virtual void onInit(Window *window) {
        cerr << "FakeGglListener::init()" << endl;
        cerr << glGetString(GL_VERSION) << endl;
        glViewport(0, 0, 512, 512);
    }
    virtual void onDisplay(Window *window) {
        cerr << "FakeGglListener::display()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void onDestroy(Window *window) {
        cerr << "FakeGglListener::destroy()" << endl;
    }
    virtual void onKey(Window *window, const WindowEvent &event) {
        cerr << "FakeGglListener::onKey()" << endl;
        int trigger = event.getTrigger();
        
        if (trigger == GGL_a) {
            cerr << 'a' << endl;
        } else if (trigger == GGL_A) {
            cerr << "A" << endl;
        } else if (trigger == GGL_UP) {
            cerr << "Up" << endl;
        } else if (trigger == GGL_ESCAPE) {
            cerr << "Escape" << endl;
            window->close();
        }
    }
};

/**
 * Ensures window can be opened.
 */
void WindowCocoaTest::testOpen() {
    
    WindowFactory factory;
    Window *window = factory.createWindow();
    
    window->addWindowListener(new FakeWindowListener());
    Window::open(window);
}
}

/*
 * Runs the program.
 */
int main(int argc, char *argv[]) {
    
    Ggl::WindowCocoaTest test;
    
    test.testOpen();
}
