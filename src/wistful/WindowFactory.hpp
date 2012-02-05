/*
 * WindowFactory.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_WINDOWFACTORY_HPP
#define WISTFUL_WINDOWFACTORY_HPP
#include "wistful/common.h"
#include "wistful/Window.hpp"
#if defined(HAVE_COCOA)
#include "wistful/cocoa/WindowCocoa.hpp"
#elif defined(HAVE_GLX)
#include "wistful/glx/WindowGlx.hpp"
#endif
namespace Wistful {


/**
 * Utility for creating windows.
 */
class WindowFactory {
public:
    WindowFactory();
    virtual ~WindowFactory();
    Window* createWindow();
    Window* createWindow(const WindowFormat &format);
private:
    WindowFormat defaultWindowFormat;
// Constructors
    WindowFactory(const WindowFactory&);
    WindowFactory& operator=(const WindowFactory&);
};

} /* namespace Wistful */
#endif
