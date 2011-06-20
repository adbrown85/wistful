/*
 * GglConfigFactoryGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIGFACTORYGLX_HPP
#define GGLCONFIGFACTORYGLX_HPP
#include "ggl/common.h"
#include "ggl/window/GglWindowFormat.hpp"


/**
 * Utility for creating OpenGL configurations.
 */
class GglConfigFactoryGlx {
public:
    GglConfigFactoryGlx();
    virtual ~GglConfigFactoryGlx();
    virtual GLXFBConfig create(const Ggl::WindowFormat &wf);
    virtual GLXFBConfig create(const std::map<int,int> &requirements);
private:
    Display *display;
// Helpers
    static Display* createDisplay();
    static const int* toArray(const std::map<int,int> &m);
};

#endif
