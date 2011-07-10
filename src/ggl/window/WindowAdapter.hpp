/*
 * WindowAdapter.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_WINDOWADAPTER_HPP
#define GGL_WINDOWADAPTER_HPP
#include "ggl/common.h"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowListener.hpp"
namespace Ggl {


/**
 * @brief Skeletal implementation of WindowListener.
 */
class WindowAdapter : public WindowListener {
public:
    WindowAdapter();
    virtual ~WindowAdapter();
    virtual void onInit(Window *window);
    virtual void onDisplay(Window *window);
    virtual void onKey(Window *window, const WindowEvent &we);
    virtual void onDestroy(Window *window);
};

} /* namespace Ggl */
#endif
