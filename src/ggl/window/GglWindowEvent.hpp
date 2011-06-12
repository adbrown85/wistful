/*
 * GglWindowEvent.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWEVENT_HPP
#define GGLWINDOWEVENT_HPP
#include "ggl/ggl_common.h"


enum GglWindowEventType {
    DESTROY,
    MAP,
    EXPOSE,
    RESHAPE,
    KEY,
    MOUSE,
    OTHER
};


class GglWindowEvent {
public:
    GglWindowEvent(GglWindowEventType type);
    virtual ~GglWindowEvent();
    virtual GglWindowEventType getType();
    virtual GLuint getTrigger();
    virtual void setTrigger(GLuint trigger);
private:
    GglWindowEventType type;
    GLuint trigger;
};

#endif
