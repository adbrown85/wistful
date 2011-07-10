/*
 * WindowEvent.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/WindowEvent.hpp"
using namespace Ggl;
using namespace std;

WindowEvent::WindowEvent(const Window *window, GLuint trigger) {
    this->window = window;
    this->trigger = trigger;
}

WindowEvent::~WindowEvent() {
    ;
}

GLuint WindowEvent::getTrigger() const {
    return trigger;
}

const Window* WindowEvent::getWindow() const {
    return window;
}
