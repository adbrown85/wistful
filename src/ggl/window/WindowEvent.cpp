/*
 * WindowEvent.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/WindowEvent.hpp"
using namespace Ggl;

WindowEvent::WindowEvent(WindowEventType type) {
    this->type = type;
}

WindowEvent::~WindowEvent() {
    ;
}

WindowEventType WindowEvent::getType() {
    return type;
}

GLuint WindowEvent::getTrigger() {
    return trigger;
}

void WindowEvent::setTrigger(GLuint trigger) {
    this->trigger = trigger;
}
