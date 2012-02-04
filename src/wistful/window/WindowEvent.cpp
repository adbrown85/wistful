/*
 * WindowEvent.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "wistful/window/WindowEvent.hpp"
using namespace Wistful;
using namespace std;

WindowEvent::WindowEvent(Wistful::Window *window, GLuint trigger) {
    this->window = window;
    this->trigger = trigger;
}

WindowEvent::~WindowEvent() {
    ;
}

GLuint WindowEvent::getTrigger() const {
    return trigger;
}

Wistful::Window* WindowEvent::getWindow() const {
    return window;
}
