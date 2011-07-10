/*
 * WindowListener.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_WINDOWLISTENER_HPP
#define GGL_WINDOWLISTENER_HPP
#include "ggl/common.h"
#include "ggl/window/WindowEvent.hpp"
namespace Ggl {


/**
 * @brief Object that listens to GGL events.
 */
class WindowListener {
public:
    WindowListener();
    virtual ~WindowListener();
    virtual void onInit(const WindowEvent &e) = 0;
    virtual void onDisplay(const WindowEvent &e) = 0;
    virtual void onDestroy(const WindowEvent &e) = 0;
    virtual void onKey(const WindowEvent &e) = 0;
};

}
#endif
