/*
 * GglWindowFactoryGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowFactoryGlx.hpp"

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
#ifdef HAVE_GLX
    return new GglWindowGlx();
#endif
    return NULL;
}

