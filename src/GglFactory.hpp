/*
 * GglFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLFACTORY_HPP
#define GGLFACTORY_HPP
#include "ggl_common.h"
#include "GglConfigFactory.hpp"
#include "GglConfigFactoryGlx.hpp"
#include "GglWindowFactory.hpp"
#include "GglWindowFactoryGlx.hpp"


/**
 * Utility for retrieving GGL objects.
 */
class GglFactory {
public:
    static GglWindow* createWindow();
    static GglConfigFactory* getConfigFactory();
    static GglWindowFactory* getWindowFactory();
};

#endif
