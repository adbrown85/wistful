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
    virtual WindowEventType getType() const;
    virtual GLuint getTrigger() const;
    virtual void setTrigger(GLuint trigger);
private:
    WindowEventType type;
    GLuint trigger;
};

}
#endif
