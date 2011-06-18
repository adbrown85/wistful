/*
 * GglWindowCocoaTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/GglWindowFactory.hpp"
#include "ggl/window/cocoa/GglWindowCocoa.hpp"
using namespace std;

/**
 * Test for GglWindowCoca.
 */
class GglWindowCocoaTest {
public:
    void testOpen();
};

class FakeWindowListener : public GglWindowListener {
public:
    virtual void onInit(GglWindow *window) {
        cerr << "FakeGglListener::init()" << endl;
        cerr << glGetString(GL_VERSION) << endl;
        glViewport(0, 0, 512, 512);
    }
    virtual void onDisplay(GglWindow *window) {
        cerr << "FakeGglListener::display()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void onDestroy(GglWindow *window) {
        cerr << "FakeGglListener::destroy()" << endl;
    }
    virtual void onKey(GglWindow *window, GglWindowEvent &event) {
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
void GglWindowCocoaTest::testOpen() {
    
    GglWindowFactory factory;
    GglWindow *window = factory.createWindow();
    
    window->addWindowListener(new FakeWindowListener());
    GglWindow::open(window);
}

/*
 * Runs the program.
 */
int main(int argc, char *argv[]) {
    
    GglWindowCocoaTest test;
    
    test.testOpen();
}
