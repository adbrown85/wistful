/*
 * GglWindowCocoaTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowCocoa.hpp"
#include "GglWindowFactory.hpp"
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
    }
    virtual void onDisplay(GglWindow *window) {
        cerr << "FakeGglListener::display()" << endl;
        glViewport(0, 0, 512, 512);
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    virtual void onDestroy(GglWindow *window) {
        cerr << "FakeGglListener::destroy()" << endl;
    }
    virtual void onKey(GglWindow *window, GglWindowEvent &event) {
        cerr << "FakeGglListener::onKey()" << endl;
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
