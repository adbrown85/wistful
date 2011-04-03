/*
 * GglFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglFactory.hpp"

/**
 * Obtains a configuration factory for the current environment.
 * 
 * @return Pointer to new config factory, or NULL if none available
 */
GglConfigFactory* GglFactory::getConfigFactory() {
#ifdef HAVE_GLX
    return new GglConfigFactoryGlx();
#endif
    return NULL;
}

/**
 * Obtains a window factory for the current environment.
 * 
 * @return Pointer to new window factory, or NULL if none available
 */
GglWindowFactory* GglFactory::getWindowFactory() {
#ifdef HAVE_GLX
    return new GglWindowFactoryGlx();
#endif
    return NULL;
}
