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
#include "GglWindowFactory.hpp"
#ifdef HAVE_GLX
#include "GglConfigFactoryGlx.hpp"
#include "GglWindowFactoryGlx.hpp"
#endif


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
