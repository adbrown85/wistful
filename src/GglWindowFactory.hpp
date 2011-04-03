/*
 * GglWindowFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWFACTORY_HPP
#define GGLWINDOWFACTORY_HPP
#include "ggl_common.h"
#include "GglWindow.hpp"


/**
 * Abstract base class for a utility to create windows.
 */
class GglWindowFactory {
public:
    GglWindowFactory();
    virtual ~GglWindowFactory();
    virtual GglWindow* create() = 0;
};

#endif
