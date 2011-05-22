/*
 * GglWindowFactoryCocoa.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowFactoryCocoa.hpp"

/**
 * Creates a window factory for Cocoa.
 */
GglWindowFactoryCocoa::GglWindowFactoryCocoa() {
    ;
}

/**
 * Destroys the window factory.
 */
GglWindowFactoryCocoa::~GglWindowFactoryCocoa() {
    ;
}

/**
 * Creates a window.
 * 
 * @return Pointer to the new window
 */
GglWindow* GglWindowFactoryCocoa::create() {
    return new GglWindowCocoa();
}
