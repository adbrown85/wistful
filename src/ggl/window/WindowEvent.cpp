/*
 * WindowEvent.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/WindowEvent.hpp"

Ggl::WindowEvent::WindowEvent(Ggl::WindowEventType type) {
    this->type = type;
}

Ggl::WindowEvent::~WindowEvent() {
    ;
}

Ggl::WindowEventType Ggl::WindowEvent::getType() {
    return type;
}

GLuint Ggl::WindowEvent::getTrigger() {
    return trigger;
}

void Ggl::WindowEvent::setTrigger(GLuint trigger) {
    this->trigger = trigger;
}
