/*
 * GglConfigFactoryGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIGFACTORYGLX_HPP
#define GGLCONFIGFACTORYGLX_HPP
#include "ggl_common.h"
#include "GglWindowFormat.hpp"


/**
 * Utility for creating OpenGL configurations.
 */
class GglConfigFactoryGlx {
public:
    GglConfigFactoryGlx();
    virtual ~GglConfigFactoryGlx();
    virtual GLXFBConfig create(const GglWindowFormat &wf);
    virtual GLXFBConfig create(const map<int,int> &requirements);
private:
    Display *display;
// Helpers
    static Display* createDisplay();
    static const int* toArray(const map<int,int> &m);
};

#endif
