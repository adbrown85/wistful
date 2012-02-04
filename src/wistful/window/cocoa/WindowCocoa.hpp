/*
 * WindowCocoa.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_WINDOWCOCOA_HPP
#define WISTFUL_WINDOWCOCOA_HPP
#include "wistful/common.h"
#import <Cocoa/Cocoa.h>
#include "wistful/window/Window.hpp"
namespace Wistful {


/**
 * Observer of an application.
 */
class ApplicationListener {
public:
    ApplicationListener() {}
    virtual ~ApplicationListener() {}
    virtual void onApplicationTerminate() = 0;
};


/**
 * Observer of an OpenGL view.
 */
class OpenGLViewListener {
public:
    OpenGLViewListener() {}
    virtual ~OpenGLViewListener() {}
    virtual void onOpenGLViewInit() = 0;
    virtual void onOpenGLViewDisplay() = 0;
    virtual void onOpenGLViewDestroy() = 0;
    virtual void onOpenGLViewKey(int key) = 0;
};


/**
 * OpenGL Window implemented with Cocoa.
 */
class WindowCocoa : public Window,
                    public ApplicationListener,
                    public OpenGLViewListener {
public:
    WindowCocoa(const WindowFormat &wf);
    virtual ~WindowCocoa();
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
    static GLuint* toArray(const WindowFormat &wf);
    static std::list<GLuint> toList(const WindowFormat &wf);
// Constructors
    WindowCocoa(const WindowCocoa&);
    WindowCocoa& operator=(const WindowCocoa&);
};

} // namespace Wistful


/*
 * Application delegate for window.
 */
@interface WistfulApplicationDelegate: NSObject <NSApplicationDelegate> {
    Wistful::ApplicationListener *applicationListener;
}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)app;
- (void)applicationWillTerminate:(NSNotification*)notification;
- (void)setApplicationListener:(Wistful::ApplicationListener*)listener;
@end


/*
 * OpenGL view for window.
 */
@interface WistfulOpenGLView : NSOpenGLView {
    Wistful::OpenGLViewListener *openGLViewListener;
}
- (void)keyDown:(NSEvent*)event;
- (void)drawRect:(NSRect)dirtyRect;
- (void)prepareOpenGL;
- (void)setOpenGLViewListener:(Wistful::OpenGLViewListener*)listener;
@end

#endif
