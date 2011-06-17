/*
 * GglWindowCocoa.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWCOCOA_HPP
#define GGLWINDOWCOCOA_HPP
#include "ggl/common.h"
#import <Cocoa/Cocoa.h>
#include "ggl/window/GglWindow.hpp"


/**
 * @brief Observer of an application.
 */
class GglApplicationListener {
public:
    GglApplicationListener() {}
    virtual ~GglApplicationListener() {}
    virtual void onApplicationTerminate() = 0;
};


/**
 * @brief Observer of an OpenGL view.
 */
class GglOpenGLViewListener {
public:
    GglOpenGLViewListener() {}
    virtual ~GglOpenGLViewListener() {}
    virtual void onOpenGLViewInit() = 0;
    virtual void onOpenGLViewDisplay() = 0;
    virtual void onOpenGLViewDestroy() = 0;
    virtual void onOpenGLViewKey(int key) = 0;
};


/**
 * @brief Window implemented with Cocoa.
 */
class GglWindowCocoa : public GglWindow,
                       public GglApplicationListener,
                       public GglOpenGLViewListener {
public:
    GglWindowCocoa(const GglWindowFormat &wf);
    virtual ~GglWindowCocoa();
    virtual void doActivateContext();
    virtual void doActivateWindow();
    virtual void doClose();
    virtual void doCreateConnection() throw (std::exception);
    virtual void doCreateWindow() throw (std::exception);
    virtual void doCreateContext()throw (std::exception);
    virtual void doDestroyConnection();
    virtual void doDestroyContext();
    virtual void doDestroyWindow();
    virtual void doFlush();
    virtual void doRun();
    virtual void onApplicationTerminate();
    virtual void onOpenGLViewInit();
    virtual void onOpenGLViewDisplay();
    virtual void onOpenGLViewDestroy();
    virtual void onOpenGLViewKey(int key);
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
    static GLuint* toArray(const GglWindowFormat &wf);
    static std::list<GLuint> toList(const GglWindowFormat &wf);
};


/*
 * Application delegate for window.
 */
@interface MyApplicationDelegate: NSObject <NSApplicationDelegate> {
    GglApplicationListener *applicationListener;
}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app;
- (void)applicationWillTerminate:(NSNotification*)notification;
- (void)setApplicationListener:(GglApplicationListener*)listener;
@end


/*
 * OpenGL view for window.
 */
@interface MyOpenGLView : NSOpenGLView {
    GglOpenGLViewListener *openGLViewListener;
}
- (void)keyDown:(NSEvent*)event;
- (void)drawRect:(NSRect)dirtyRect;
- (void)prepareOpenGL;
- (void)setOpenGLViewListener:(GglOpenGLViewListener*)listener;
@end


#endif
