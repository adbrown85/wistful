/*
 * GglConfigGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIGGLX_HPP
#define GGLCONFIGGLX_HPP
#include "ggl_common.h"
#ifdef HAVE_GLX
#include "GglConfig.hpp"


/** @brief <i>Builder</i> for @GglConfigGlx. */
class GglConfigGlxBuilder : public GglConfigBuilder {
public:
    virtual ~GglConfigGlxBuilder() {}
    GLXFBConfig glxFBConfig;                // GLX Framebuffer configuration
    int id;                                 // Identifier from X
};


/** @brief OpenGL configuration with GLX. */
class GglConfigGlx : public GglConfig {
public:
    GglConfigGlx(GglConfigGlxBuilder *b);
    virtual ~GglConfigGlx() {}
    virtual GLXFBConfig getFBConfig();
    virtual int getId();
private:
    GLXFBConfig glxFBConfig;                // GLX Framebuffer configuration
    int id;                                 // Identifier from GLX
};

#endif // HAVE_GLX
#endif // GGL_CONFIGGLX_HPP
