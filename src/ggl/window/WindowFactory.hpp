/*
 * GglWindowFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_WINDOWFACTORY_HPP
#define GGL_WINDOWFACTORY_HPP
#include "ggl/common.h"
#include "ggl/window/Window.hpp"
#if defined(HAVE_COCOA)
#include "ggl/window/cocoa/WindowCocoa.hpp"
#elif defined(HAVE_GLX)
#include "ggl/window/glx/WindowGlx.hpp"
#endif
namespace Ggl {


/**
 * Abstract base class for a utility to create windows.
 */
class WindowFactory {
public:
    WindowFactory();
    virtual ~WindowFactory();
    Window* createWindow();
    Window* createWindow(const WindowFormat &wf);
private:
    WindowFormat defaultWindowFormat;
};

}
#endif