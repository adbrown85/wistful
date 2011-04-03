/*
 * GglConfig.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIG_HPP
#define GGLCONFIG_HPP
#include "ggl_common.h"


/** @brief <i>Builder</i> for @GglConfig. */
class GglConfigBuilder {
public:
    GglConfigBuilder();
    virtual ~GglConfigBuilder() {}
    int red;                                // Red size
    int green;                              // Green size
    int blue;                               // Blue size
    int alpha;                              // Alpha size
    int depth;                              // Depth size
    int stencil;                            // Stencil size
    bool doubleBuffered;                    // True if front and back buffers
};


/** @brief OpenGL configuration. */
class GglConfig {
public:
    GglConfig(GglConfigBuilder *b);
    virtual ~GglConfig() {}
    virtual int getRedSize() const;
    virtual int getGreenSize() const;
    virtual int getBlueSize() const;
    virtual int getAlphaSize() const;
    virtual int getDepthSize() const;
    virtual int getStencilSize() const;
    virtual bool isDoubleBuffered() const;
private:
    int red;                                // Red size
    int green;                              // Green size
    int blue;                               // Blue size
    int alpha;                              // Alpha size
    int depth;                              // Depth size
    int stencil;                            // Stencil size
    bool doubleBuffered;                    // True if front and back buffers
};

#endif
