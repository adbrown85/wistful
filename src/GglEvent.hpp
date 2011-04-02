/*
 * GglEvent.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLEVENT_HPP
#define GGLEVENT_HPP
#include "common.h"


enum GglEventType {
    DESTROY,
    RESHAPE,
    KEY,
    MOUSE,
    OTHER
};


class GglEvent {
public:
    GglEvent(GglEventType type);
    virtual ~GglEvent();
    virtual GglEventType getType();
    virtual GLuint getTrigger();
    virtual void setTrigger(GLuint trigger);
private:
    GglEventType type;
    GLuint trigger;
};

#endif
