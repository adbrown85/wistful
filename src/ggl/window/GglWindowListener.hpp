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


/* Forward declaration of window. */
namespace Ggl {
class Window;
}


/**
 * @brief Object that listens to GGL events.
 */
class GglWindowListener {
public:
    GglWindowListener();
    virtual ~GglWindowListener();
    virtual void onInit(Ggl::Window *window) = 0;
    virtual void onDisplay(Ggl::Window *window) = 0;
    virtual void onDestroy(Ggl::Window *window) = 0;
    virtual void onKey(Ggl::Window *window, Ggl::WindowEvent &event) = 0;
};

#endif
