/*
 * WindowFactory.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "wistful/WindowFactory.hpp"
using namespace Wistful;
using namespace std;

/**
 * Creates a window factory.
 */
WindowFactory::WindowFactory() {
    ;
}

/**
 * Destroys the window factory.
 */
WindowFactory::~WindowFactory() {
    ;
}

/**
 * Creates a window.
 *
 * @return Pointer to the new window
 */
Wistful::Window* WindowFactory::createWindow() {
#if defined(HAVE_COCOA)
    return new WindowCocoa(defaultWindowFormat);
#elif defined(HAVE_GLX)
    return new WindowGlx(defaultWindowFormat);
#endif
}

/**
 * Creates a window.
 *
 * @param format Format to use for the window
 * @return Pointer to the new window
 */
Wistful::Window*
WindowFactory::createWindow(const WindowFormat &format) {
#if defined(HAVE_COCOA)
    return new WindowCocoa(format);
#elif defined(HAVE_GLX)
    return new WindowGlx(format);
#endif
}
