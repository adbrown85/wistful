/*
 * WindowGlxTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "wistful/WindowFactory.hpp"
#include <iostream>
using namespace Wistful;
using namespace std;


/**
 * Observer of the window.
 */
class FakeWindowListener : public WindowListener {
public:

    /**
     * Responds to the window opening.
     */
    virtual void onWindowOpen(const WindowEvent &e) {
        cerr << "FakeWistfulListener::onWindowOpen()" << endl;
    }

    /**
     * Responds to the window being painted.
     */
    virtual void onWindowPaint(const WindowEvent &e) {
        cerr << "FakeWistfulListener::onWindowPaint()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    /**
     * Responds to a key being pressed in the window.
     */
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

    /**
     * Responds to the window being closed.
     */
    virtual void onWindowClose(const WindowEvent &e) {
        cerr << "FakeWistfulListener::onWindowClose()" << endl;
    }
};


/**
 * Runs the test.
 */
int main(int argc, char *argv[]) {

    WindowFactory factory;
    Wistful::Window *window = factory.createWindow();

    window->setLocation(50, 50);
    window->setSize(640, 480);
    window->addWindowListener(new FakeWindowListener());
    Wistful::Window::open(window);

    cerr << "End of Wistful::WindowGlxTest::testOpen()" << endl;
}
