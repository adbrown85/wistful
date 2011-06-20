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
GglWindowFactory::GglWindowFactory() {
    ;
}

/**
 * Destroys the window factory.
 */
GglWindowFactory::~GglWindowFactory() {
    ;
}

/**
 * Creates a window.
 * 
 * @return Pointer to the new window
 */
Ggl::Window* GglWindowFactory::createWindow() {
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
GglWindowFactory::createWindow(const GglWindowFormat &wf) {
#if defined(HAVE_COCOA)
    return new GglWindowCocoa(wf);
#elif defined(HAVE_GLX)
    return new GglWindowGlx(wf);
#endif
}
