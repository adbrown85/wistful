/*
 * GglConfigFactoryGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIGFACTORYGLX_HPP
#define GGLCONFIGFACTORYGLX_HPP
#include "ggl_common.h"
#include "GglConfigGlx.hpp"
#include "GglException.hpp"


/** Utility for creating OpenGL configurations. */
class GglConfigFactoryGlx {
public:
    GglConfigFactoryGlx();
    virtual ~GglConfigFactoryGlx();
    virtual GglConfig* create(const map<int,int> &requirements);
private:
    Display *display;
    map<int,GglConfig*> configs;
// Helpers
    static Display* createDisplay();
    GglConfig* doCreate(GLXFBConfig &fbc);
    GglConfig* find(int id);
    static const int* toArray(const map<int,int> &m);
    int getValue(GLXFBConfig fbc, int key);
};

#endif
