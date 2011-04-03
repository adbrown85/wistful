/*
 * GglWindowFactoryGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWFACTORYGLX_HPP
#define GGLWINDOWFACTORYGLX_HPP
#include "ggl_common.h"
#include "GglWindowFactory.hpp"
#include "GglWindowGlx.hpp"


/**
 * Utility for creating windows with GLX.
 */
class GglWindowFactoryGlx : public GglWindowFactory {
public:
    GglWindowFactoryGlx();
    virtual ~GglWindowFactoryGlx();
    virtual GglWindow* create();
};

#endif
