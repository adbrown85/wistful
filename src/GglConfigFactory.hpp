/*
 * GglConfigFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIGFACTORY_HPP
#define GGLCONFIGFACTORY_HPP
#include "ggl_common.h"
#include "GglConfig.hpp"
#include "GglException.hpp"


/** Utility for creating OpenGL configurations. */
class GglConfigFactory {
public:
    GglConfigFactory();
    virtual ~GglConfigFactory();
    virtual GglConfig* create(const map<int,int> &requirements) = 0;
protected:
    void add(int id, GglConfig *config);
    GglConfig* find(int id);
private:
    map<int,GglConfig*> configs;
};

#endif
