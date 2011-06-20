/*
 * GglWindowFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWFACTORY_HPP
#define GGLWINDOWFACTORY_HPP
#include "ggl/common.h"
#include "ggl/window/GglWindow.hpp"
#if defined(HAVE_COCOA)
#include "ggl/window/cocoa/GglWindowCocoa.hpp"
#elif defined(HAVE_GLX)
#include "ggl/window/glx/GglWindowGlx.hpp"
#endif
namespace Ggl {


/**
 * Abstract base class for a utility to create windows.
 */
class WindowFactory {
public:
    WindowFactory();
    virtual ~WindowFactory();
    Ggl::Window* createWindow();
    Ggl::Window* createWindow(const GglWindowFormat &wf);
private:
    GglWindowFormat defaultWindowFormat;
};

}
#endif
