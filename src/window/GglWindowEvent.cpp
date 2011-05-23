/*
 * GglWindowEvent.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowEvent.hpp"

GglWindowEvent::GglWindowEvent(GglWindowEventType type) {
    this->type = type;
}

GglWindowEvent::~GglWindowEvent() {
    ;
}

GglWindowEventType GglWindowEvent::getType() {
    return type;
}

GLuint GglWindowEvent::getTrigger() {
    return trigger;
}

void GglWindowEvent::setTrigger(GLuint trigger) {
    this->trigger = trigger;
}
