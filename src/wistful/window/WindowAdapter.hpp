/*
 * WindowAdapter.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_WINDOWADAPTER_HPP
#define WISTFUL_WINDOWADAPTER_HPP
#include "wistful/common.h"
#include "wistful/window/Window.hpp"
#include "wistful/window/WindowListener.hpp"
namespace Wistful {


/**
 * Skeletal implementation of %WindowListener.
 */
class WindowAdapter : public WindowListener {
public:
    WindowAdapter();
    virtual ~WindowAdapter();
    virtual void onWindowOpen(const WindowEvent &e);
    virtual void onWindowPaint(const WindowEvent &e);
    virtual void onWindowKey(const WindowEvent &e);
    virtual void onWindowClose(const WindowEvent &e);
};

} /* namespace Wistful */
#endif
