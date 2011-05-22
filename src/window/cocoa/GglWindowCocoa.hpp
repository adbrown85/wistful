/*
 * GglWindowCocoa.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWCOCOA_HPP
#define GGLWINDOWCOCOA_HPP
#include "ggl_common.h"
#import <Cocoa/Cocoa.h>
#include "GglWindow.hpp"


/**
 * @brief Window implemented with Cocoa.
 */
class GglWindowCocoa : public GglWindow {
public:
    GglWindowCocoa();
    virtual ~GglWindowCocoa();
    virtual void doActivateContext();
    virtual void doActivateWindow();
    virtual void doCreateConnection() throw (GglException);
    virtual void doCreateWindow() throw (GglException);
    virtual void doCreateContext()throw (GglException);
    virtual void doDestroyConnection();
    virtual void doDestroyContext();
    virtual void doDestroyWindow();
    virtual void doFlush();
    virtual void doRun();
    virtual GglEvent doGetEvent();
private:
    NSAutoreleasePool *pool;
    NSApplication *application;
    NSWindow *window;
// Helpers
    NSUInteger createWindowStyle();
};

#endif
