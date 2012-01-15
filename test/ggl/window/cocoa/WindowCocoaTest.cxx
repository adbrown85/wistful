/*
 * WindowCocoaTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "ggl/window/cocoa/WindowCocoaTest.hxx"
using namespace std;
using namespace Ggl;

void FakeWindowListener::onWindowOpen(const WindowEvent &e) {
    cerr << "FakeGglListener::onWindowOpen()" << endl;

    cerr << glGetString(GL_VERSION) << endl;
    glViewport(0, 0, 512, 512);
}

void FakeWindowListener::onWindowPaint(const WindowEvent &e) {
    cerr << "FakeGglListener::onWindowPaint()" << endl;

    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void FakeWindowListener::onWindowKey(const WindowEvent &e) {
    cerr << "FakeGglListener::onWindowKey()" << endl;

    int trigger = e.getTrigger();

    if (trigger == GGL_KEY_a) {
        cerr << 'a' << endl;
    } else if (trigger == GGL_KEY_A) {
        cerr << "A" << endl;
    } else if (trigger == GGL_KEY_UP) {
        cerr << "Up" << endl;
    } else if (trigger == GGL_KEY_ESCAPE) {
        cerr << "Escape" << endl;
        e.getWindow()->close();
    }
}

void FakeWindowListener::onWindowClose(const WindowEvent &e) {
    cerr << "FakeGglListener::onWindowClose()" << endl;
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
