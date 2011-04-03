/*
 * GglWindowFactoryGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowFactoryGlx.hpp"
#ifdef HAVE_GLX

/**
 * Creates a window factory for GLX.
 */
GglWindowFactoryGlx::GglWindowFactoryGlx() {
    ;
}

/**
 * Destroys the factory.
 */
GglWindowFactoryGlx::~GglWindowFactoryGlx() {
    ;
}

/**
 * Creates a window for use with GLX.
 * 
 * @return Resulting window
 */

GglWindow* GglWindowFactoryGlx::create() {
    return new GglWindowGlx();
}

#endif // HAVE_GLX
