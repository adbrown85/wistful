/*
 * WindowFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/WindowFactory.hpp"
using namespace Ggl;
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
Ggl::Window* WindowFactory::createWindow() {
#if defined(HAVE_COCOA)
    return new WindowCocoa(defaultWindowFormat);
#elif defined(HAVE_GLX)
    return new WindowGlx(defaultWindowFormat);
#endif
}

/**
 * Creates a window.
 * 
 * @param wf Format to use for the window
 * @return Pointer to the new window
 */
Ggl::Window*
WindowFactory::createWindow(const WindowFormat &wf) {
#if defined(HAVE_COCOA)
    return new WindowCocoa(wf);
#elif defined(HAVE_GLX)
    return new WindowGlx(wf);
#endif
}
