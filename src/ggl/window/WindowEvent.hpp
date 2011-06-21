/*
 * WindowEvent.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_WINDOWEVENT_HPP
#define GGL_WINDOWEVENT_HPP
#include "ggl/common.h"
namespace Ggl {


enum WindowEventType {
    WINDOW_DESTROY_EVENT,
    WINDOW_MAP_EVENT,
    WINDOW_EXPOSE_EVENT,
    WINDOW_RESHAPE_EVENT,
    WINDOW_KEY_EVENT,
    WINDOW_MOUSE_EVENT,
    WINDOW_OTHER_EVENT
};


class WindowEvent {
public:
    WindowEvent(WindowEventType type);
    virtual ~WindowEvent();
    virtual WindowEventType getType() const;
    virtual GLuint getTrigger() const;
    virtual void setTrigger(GLuint trigger);
private:
    WindowEventType type;
    GLuint trigger;
};

}
#endif
