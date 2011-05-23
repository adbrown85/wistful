/*
 * GglWindowCocoaTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowCocoa.hpp"
#include "GglFactory.hpp"
using namespace std;

/**
 * Test for GglWindowCoca.
 */
class GglWindowCocoaTest {
public:
    void testOpen();
};

class FakeGglListener : public GglListener {
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
    virtual void onKey(GglWindow *window, GglEvent &event) {
        cerr << "FakeGglListener::onKey()" << endl;
    }
};

/**
 * Ensures window can be opened.
 */
void GglWindowCocoaTest::testOpen() {
    
    GglWindowFactory *factory = GglFactory::getWindowFactory();
    GglWindow *window = factory->create();
    
    window->addListener(new FakeGglListener());
    GglWindow::open(window);
}

/*
 * Runs the program.
 */
int main(int argc, char *argv[]) {
    
    GglWindowCocoaTest test;
    
    test.testOpen();
}
