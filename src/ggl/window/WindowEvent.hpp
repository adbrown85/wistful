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


/* Forward declaration */
class Window;

/**
 * Event fired from a window.
 */
class WindowEvent {
public:
    explicit WindowEvent(Window *window, GLuint trigger=0);
    virtual ~WindowEvent();
    virtual Window* getWindow() const;
    virtual GLuint getTrigger() const;
private:
    Window *window;
    GLuint trigger;
};

}
#endif
