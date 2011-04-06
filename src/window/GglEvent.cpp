/*
 * GglEvent.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglEvent.hpp"

GglEvent::GglEvent(GglEventType type) {
    this->type = type;
}

GglEvent::~GglEvent() {
    ;
}

GglEventType GglEvent::getType() {
    return type;
}

GLuint GglEvent::getTrigger() {
    return trigger;
}

void GglEvent::setTrigger(GLuint trigger) {
    this->trigger = trigger;
}
