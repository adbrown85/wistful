/*
 * GglConfigFactoryGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIGFACTORYGLX_HPP
#define GGLCONFIGFACTORYGLX_HPP
#include "ggl_common.h"
#include "GglConfigFactory.hpp"
#include "GglConfigGlx.hpp"
#include "GglWindowFormat.hpp"


/**
 * Utility for creating OpenGL configurations.
 */
class GglConfigFactoryGlx : public GglConfigFactory {
public:
    GglConfigFactoryGlx();
    virtual ~GglConfigFactoryGlx();
    virtual GglConfig* create(const GglWindowFormat &wf);
    virtual GglConfig* create(const map<int,int> &requirements);
private:
    Display *display;
// Helpers
    static Display* createDisplay();
    GglConfig* doCreate(GLXFBConfig &fbc);
    static const int* toArray(const map<int,int> &m);
    int getValue(GLXFBConfig fbc, int key);
};

#endif
