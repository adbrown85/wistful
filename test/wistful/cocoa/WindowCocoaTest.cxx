/*
 * WindowCocoaTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "wistful/common.h"
#include <iostream>
#include "wistful/Window.hpp"
#include "wistful/WindowFactory.hpp"
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
    void onWindowOpen(const WindowEvent &e) {
        cerr << "FakeWindowListener::onWindowOpen()" << endl;
        cerr << glGetString(GL_VERSION) << endl;
        glViewport(0, 0, 512, 512);
    }

    /**
     * Responds to the window being painted.
     */
    void onWindowPaint(const WindowEvent &e) {
        cerr << "FakeWindowListener::onWindowPaint()" << endl;
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    /**
     * Responds to a key being pressed in the window.
     */
    void onWindowKey(const WindowEvent &e) {
        cerr << "FakeWindowListener::onWindowKey()" << endl;
        int trigger = e.getTrigger();
        if (trigger == WISTFUL_KEY_a) {
            cerr << 'a' << endl;
        } else if (trigger == WISTFUL_KEY_A) {
            cerr << "A" << endl;
        } else if (trigger == WISTFUL_KEY_UP) {
            cerr << "Up" << endl;
        } else if (trigger == WISTFUL_KEY_ESCAPE) {
            cerr << "Escape" << endl;
            e.getWindow()->close();
        }
    }

    /**
     * Responds to the window closing.
     */
    void onWindowClose(const WindowEvent &e) {
        cerr << "FakeWindowListener::onWindowClose()" << endl;
    }
};


/*
 * Runs the test.
 */
int main(int argc, char *argv[]) {

    WindowFactory factory;
    Window *window = factory.createWindow();

    window->addWindowListener(new FakeWindowListener());
    Window::open(window);
    return 0;
}
