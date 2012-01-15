/*
 * WindowEvent.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "ggl/window/WindowEvent.hpp"
using namespace Ggl;
using namespace std;

WindowEvent::WindowEvent(Ggl::Window *window, GLuint trigger) {
    this->window = window;
    this->trigger = trigger;
}

WindowEvent::~WindowEvent() {
    ;
}

GLuint WindowEvent::getTrigger() const {
    return trigger;
}

Ggl::Window* WindowEvent::getWindow() const {
    return window;
}
