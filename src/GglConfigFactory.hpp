/*
 * GglConfigFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIGFACTORY_HPP
#define GGLCONFIGFACTORY_HPP
#include "common.h"
#include "GglConfig.hpp"
#include "GglException.hpp"


/** Utility for creating OpenGL configurations. */
class GglConfigFactory {
public:
    GglConfigFactory();
    virtual ~GglConfigFactory();
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
