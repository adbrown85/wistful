/*
 * GglWindowListener.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWLISTENER_HPP
#define GGLWINDOWLISTENER_HPP
#include "ggl/ggl_common.h"
#include "ggl/window/GglWindowEvent.hpp"


/* Forward declaration of window. */
class GglWindow;


/**
 * @brief Object that listens to GGL events.
 */
class GglWindowListener {
public:
    GglWindowListener();
    virtual ~GglWindowListener();
    virtual void onInit(GglWindow *window) = 0;
    virtual void onDisplay(GglWindow *window) = 0;
    virtual void onDestroy(GglWindow *window) = 0;
    virtual void onKey(GglWindow *window, GglWindowEvent &event) = 0;
};

#endif
