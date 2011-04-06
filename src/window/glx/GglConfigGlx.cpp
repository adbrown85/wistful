/*
 * GglConfigGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfigGlx.hpp"

/** Creates an OpenGL configuration with GLX. */
GglConfigGlx::GglConfigGlx(GglConfigGlxBuilder *b) : GglConfig(b) {
#ifdef HAVE_GLX
    this->id = b->id;
    this->glxFBConfig = b->glxFBConfig;
#endif //HAVE_GLX
}

#ifdef HAVE_GLX

/** Returns native framebuffer configuration for GLX. */
GLXFBConfig GglConfigGlx::getFBConfig() {
    return glxFBConfig;
}

/** Returns identifier given to configuration by GLX. */
int GglConfigGlx::getId() {
    return id;
}

#endif // HAVE_GLX
