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
namespace Ggl {


/**
 * Utility for creating OpenGL configurations.
 */
class ConfigFactoryGlx {
public:
    ConfigFactoryGlx();
    virtual ~ConfigFactoryGlx();
    virtual GLXFBConfig create(const WindowFormat &wf);
    virtual GLXFBConfig create(const std::map<int,int> &requirements);
private:
    Display *display;
// Helpers
    static Display* createDisplay();
    static const int* toArray(const std::map<int,int> &m);
};

}
#endif
