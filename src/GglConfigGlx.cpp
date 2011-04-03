/*
 * GglConfigGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfigGlx.hpp"

/** Creates an OpenGL configuration with GLX. */
GglConfigGlx::GglConfigGlx(GglConfigGlxBuilder *b) : GglConfig(b) {
    this->glxFBConfig = b->glxFBConfig;
    this->id = b->id;
}

/** Returns native framebuffer configuration for GLX. */
GLXFBConfig GglConfigGlx::getFBConfig() {
    return glxFBConfig;
}

/** Returns identifier given to configuration by GLX. */
int GglConfigGlx::getId() {
    return id;
}
