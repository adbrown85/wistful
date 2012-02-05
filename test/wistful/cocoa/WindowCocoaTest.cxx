/*
 * WindowCocoaTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "wistful/cocoa/WindowCocoaTest.hxx"
#include <iostream>
using namespace std;
using namespace Wistful;

void FakeWindowListener::onWindowOpen(const WindowEvent &e) {
    cerr << "FakeWindowListener::onWindowOpen()" << endl;

    cerr << glGetString(GL_VERSION) << endl;
    glViewport(0, 0, 512, 512);
}

void FakeWindowListener::onWindowPaint(const WindowEvent &e) {
    cerr << "FakeWindowListener::onWindowPaint()" << endl;

    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void FakeWindowListener::onWindowKey(const WindowEvent &e) {
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

void FakeWindowListener::onWindowClose(const WindowEvent &e) {
    cerr << "FakeWindowListener::onWindowClose()" << endl;
}

void WindowCocoaTest::run() {

    WindowFactory factory;
    Window *window = factory.createWindow();

    window->addWindowListener(new FakeWindowListener());
    Window::open(window);
}

/*
 * Runs the program.
 */
int main(int argc, char *argv[]) {

    WindowCocoaTest test;

    test.run();
    return 0;
}
