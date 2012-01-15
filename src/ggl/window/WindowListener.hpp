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
 * Object that listens for window events.
 */
class WindowListener {
public:
    WindowListener();
    virtual ~WindowListener();
    virtual void onWindowOpen(const WindowEvent &e) = 0;
    virtual void onWindowPaint(const WindowEvent &e) = 0;
    virtual void onWindowKey(const WindowEvent &e) = 0;
    virtual void onWindowClose(const WindowEvent &e) = 0;
};

}
#endif
