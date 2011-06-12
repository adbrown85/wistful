/*
 * GglWindowFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWFACTORY_HPP
#define GGLWINDOWFACTORY_HPP
#include "ggl/ggl_common.h"
#include "ggl/window/GglWindow.hpp"
#if defined(HAVE_COCOA)
#include "ggl/window/cocoa/GglWindowCocoa.hpp"
#elif defined(HAVE_GLX)
#include "ggl/window/glx/GglWindowGlx.hpp"
#endif


/**
 * Abstract base class for a utility to create windows.
 */
class GglWindowFactory {
public:
    GglWindowFactory();
    virtual ~GglWindowFactory();
    GglWindow* createWindow();
    GglWindow* createWindow(const GglWindowFormat &wf);
private:
    GglWindowFormat defaultWindowFormat;
};

#endif
