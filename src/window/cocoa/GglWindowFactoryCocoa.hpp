/*
 * GglWindowFactoryCocoa.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWFACTORYCOCOA_HPP
#define GGLWINDOWFACTORYCOCOA_HPP
#include "ggl_common.h"
#include "GglWindowFactory.hpp"
#include "GglWindowCocoa.hpp"


/**
 * @brief Utility for creating windows with Cocoa.
 */
class GglWindowFactoryCocoa : public GglWindowFactory {
public:
    GglWindowFactoryCocoa();
    virtual ~GglWindowFactoryCocoa();
    virtual GglWindow* create();
};

#endif
