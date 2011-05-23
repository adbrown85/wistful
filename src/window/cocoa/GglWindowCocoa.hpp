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
class GglWindowCocoa : public GglWindow, public GglWindowListener {
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
    virtual void onInit(GglWindow *window);
    virtual void onDisplay(GglWindow *window);
    virtual void onDestroy(GglWindow *window);
    virtual void onKey(GglWindow *window, GglEvent &event);
private:
    NSAutoreleasePool *pool;
    NSApplication *application;
    NSWindow *window;
// Helpers
    NSUInteger createWindowStyle();
    NSMenu* createMenu();
    NSMenu* createAppleMenu();
    NSMenuItem* createAppleMenuQuitItem();
    NSMenuItem* createEmptyMenuItem();
    NSMenu* createEmptyMenu();
};

/*
 * Application delegate for window.
 */
@interface MyApplicationDelegate: NSObject <NSApplicationDelegate> {
    ;
}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app;
@end

/*
 * OpenGL view for window.
 */
@interface MyOpenGLView : NSOpenGLView {
    GglWindowListener *windowListener;
}
- (void)keyDown:(NSEvent*)event;
- (void)drawRect:(NSRect)dirtyRect;
- (void)setWindowListener:(GglWindowListener*)listener;
@end


#endif
