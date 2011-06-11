/*
 * GglWindowFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWFACTORY_HPP
#define GGLWINDOWFACTORY_HPP
#include "ggl_common.h"
#include "GglWindow.hpp"
#if defined(HAVE_COCOA)
#include "GglWindowCocoa.hpp"
#elif defined(HAVE_GLX)
#include "GglWindowGlx.hpp"
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
