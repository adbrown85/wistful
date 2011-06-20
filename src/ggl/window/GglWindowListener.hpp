/*
 * GglWindowListener.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWLISTENER_HPP
#define GGLWINDOWLISTENER_HPP
#include "ggl/common.h"
#include "ggl/window/GglWindowEvent.hpp"
namespace Ggl {


/* Forward declaration of window. */
class Window;


/**
 * @brief Object that listens to GGL events.
 */
class WindowListener {
public:
    WindowListener();
    virtual ~WindowListener();
    virtual void onInit(Window *window) = 0;
    virtual void onDisplay(Window *window) = 0;
    virtual void onDestroy(Window *window) = 0;
    virtual void onKey(Window *window, WindowEvent &event) = 0;
};

}
#endif
