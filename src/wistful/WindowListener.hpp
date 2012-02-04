/*
 * WindowListener.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_WINDOWLISTENER_HPP
#define WISTFUL_WINDOWLISTENER_HPP
#include "wistful/common.h"
#include "wistful/WindowEvent.hpp"
namespace Wistful {


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
