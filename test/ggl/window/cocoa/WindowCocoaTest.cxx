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
    virtual void onInit(const WindowEvent &e) {
        cerr << "FakeGglListener::init()" << endl;
        cerr << glGetString(GL_VERSION) << endl;
        glViewport(0, 0, 512, 512);
    }
    virtual void onDisplay(const WindowEvent &e) {
        cerr << "FakeGglListener::display()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void onDestroy(const WindowEvent &e) {
        cerr << "FakeGglListener::destroy()" << endl;
    }
    virtual void onKey(const WindowEvent &e) {
        cerr << "FakeGglListener::onKey()" << endl;
        int trigger = e.getTrigger();
        
        if (trigger == GGL_KEY_a) {
            cerr << 'a' << endl;
        } else if (trigger == GGL_KEY_A) {
            cerr << "A" << endl;
        } else if (trigger == GGL_KEY_UP) {
            cerr << "Up" << endl;
        } else if (trigger == GGL_KEY_ESCAPE) {
            cerr << "Escape" << endl;
//            window->close();
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
