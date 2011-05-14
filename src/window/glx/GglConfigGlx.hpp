/*
 * GglConfigGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIGGLX_HPP
#define GGLCONFIGGLX_HPP
#include "ggl_common.h"
#include "GglConfig.hpp"


/** @brief <i>Builder</i> for @GglConfigGlx. */
class GglConfigGlxBuilder : public GglConfigBuilder {
public:
    int id;                                 // Identifier from X
    GLXFBConfig glxFBConfig;                // GLX Framebuffer configuration
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

#endif
