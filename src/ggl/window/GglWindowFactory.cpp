/*
 * GglWindowFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowFactory.hpp"

/**
 * Creates a window factory.
 */
Ggl::WindowFactory::WindowFactory() {
    ;
}

/**
 * Destroys the window factory.
 */
Ggl::WindowFactory::~WindowFactory() {
    ;
}

/**
 * Creates a window.
 * 
 * @return Pointer to the new window
 */
Ggl::Window* Ggl::WindowFactory::createWindow() {
#if defined(HAVE_COCOA)
    return new GglWindowCocoa(defaultWindowFormat);
#elif defined(HAVE_GLX)
    return new GglWindowGlx(defaultWindowFormat);
#endif
}

/**
 * Creates a window.
 * 
 * @param wf Format to use for the window
 * @return Pointer to the new window
 */
Ggl::Window*
Ggl::WindowFactory::createWindow(const Ggl::WindowFormat &wf) {
#if defined(HAVE_COCOA)
    return new GglWindowCocoa(wf);
#elif defined(HAVE_GLX)
    return new GglWindowGlx(wf);
#endif
}
