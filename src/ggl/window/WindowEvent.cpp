/*
 * WindowEvent.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/WindowEvent.hpp"
using namespace Ggl;
using namespace std;

WindowEvent::WindowEvent(WindowEventType type) {
    this->type = type;
}

WindowEvent::~WindowEvent() {
    ;
}

WindowEventType WindowEvent::getType() const {
    return type;
}

GLuint WindowEvent::getTrigger() const {
    return trigger;
}

void WindowEvent::setTrigger(GLuint trigger) {
    this->trigger = trigger;
}
