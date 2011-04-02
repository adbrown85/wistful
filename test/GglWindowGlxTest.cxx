/*
 * GglWindowGlxTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowGlx.hpp"
#include "GglConfigFactory.hpp"
#include <iostream>
using namespace std;


/** Test for GlWindowGlx. */
class GglWindowGlxTest {
public:
    void testShow();
};

class FakeGglListener : public GglListener {
public:
    virtual void init() {
        cerr << "FakeGglListener::init()" << endl;
    }
    virtual void display() {
        cerr << "FakeGglListener::display()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void destroy() {
        cerr << "FakeGglListener::destroy()" << endl;
    }
    virtual void onKey(GglEvent &event) {
        cerr << event.getTrigger() << endl;
    }
};

/** Ensures window can be shown. */
void GglWindowGlxTest::testShow() {
    
    GglWindow *window = new GglWindowGlx();
    
    window->setSize(640, 480);
    window->addListener(new FakeGglListener());
    GglWindow::run(window);
    
    cerr << "End of GglWindowGlxTest::testShow()" << endl;
}

/** Runs the test. */
int main(int argc, char *argv[]) {
    
    GglWindowGlxTest test;
    
    test.testShow();
}
