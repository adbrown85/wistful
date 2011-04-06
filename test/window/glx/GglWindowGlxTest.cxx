/*
 * GglWindowGlxTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglFactory.hpp"
#include <iostream>
using namespace std;


/** Test for GlWindowGlx. */
class GglWindowGlxTest {
public:
    void testOpen();
};

class FakeGglListener : public GglListener {
public:
    virtual void onInit(GglWindow &window) {
        cerr << "FakeGglListener::init()" << endl;
    }
    virtual void onDisplay(GglWindow &window) {
        cerr << "FakeGglListener::display()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void onDestroy(GglWindow &window) {
        cerr << "FakeGglListener::destroy()" << endl;
    }
    virtual void onKey(GglWindow &window, GglEvent &event) {
        switch (event.getTrigger()) {
        case GGL_ESCAPE:
            cerr << "GGL_ESCAPE" << endl;
            window.close();
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
    
    GglWindow *window = GglFactory::createWindow();
    
    window->setLocation(50, 50);
    window->setSize(640, 480);
    window->addListener(new FakeGglListener());
    GglWindow::open(window);
    
    cerr << "End of GglWindowGlxTest::testOpen()" << endl;
}

/** Runs the test. */
int main(int argc, char *argv[]) {
    
    GglWindowGlxTest test;
    
    test.testOpen();
}