/*
 * GglWindowEvent.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWEVENT_HPP
#define GGLWINDOWEVENT_HPP
#include "ggl/common.h"
namespace Ggl {


enum WindowEventType {
    DESTROY,
    MAP,
    EXPOSE,
    RESHAPE,
    KEY,
    MOUSE,
    OTHER
};


class WindowEvent {
public:
    WindowEvent(WindowEventType type);
    virtual ~WindowEvent();
    virtual WindowEventType getType();
    virtual GLuint getTrigger();
    virtual void setTrigger(GLuint trigger);
private:
    WindowEventType type;
    GLuint trigger;
};

}
#endif
