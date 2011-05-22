/*
 * GglFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglFactory.hpp"

/**
 * Returns a window for the current environment.
 */
GglWindow* GglFactory::createWindow() {
    
    GglWindowFactory *factory = getWindowFactory();
    GglWindow *window = factory->create();
    
    delete factory;
    return window;
}

/**
 * Obtains a configuration factory for the current environment.
 * 
 * @return Pointer to new config factory, or NULL if none available
 */
GglConfigFactory* GglFactory::getConfigFactory() {
#if defined(HAVE_GLX)
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
#if defined(HAVE_GLX)
    return new GglWindowFactoryGlx();
#elif defined(HAVE_COCOA)
    return new GglWindowFactoryCocoa();
#endif
    return NULL;
}
