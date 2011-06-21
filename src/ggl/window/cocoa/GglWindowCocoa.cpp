/*
 * GglWindowCocoa.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/cocoa/GglWindowCocoa.hpp"

/**
 * Creates a window.
 * 
 * @param wf Configuration of window
 */
Ggl::WindowCocoa::WindowCocoa(const WindowFormat &wf) : Window(wf) {
    this->pool = NULL;
    this->application = NULL;
    this->window = NULL;
}

/**
 * Destroys the window.
 */
Ggl::WindowCocoa::~WindowCocoa() {
    ;
}

void Ggl::WindowCocoa::doActivateContext() {
    ;
}

void Ggl::WindowCocoa::doActivateWindow() {
    [window makeKeyAndOrderFront:nil];
    [application activateIgnoringOtherApps:YES];
}

void Ggl::WindowCocoa::doCreateConnection() throw(std::exception) {
    
    GglApplicationDelegate *delegate;
    NSMenu *menu;
    ProcessSerialNumber psn;
    
    pool = [[NSAutoreleasePool alloc] init];
    application = [NSApplication sharedApplication];
    
    delegate = [[GglApplicationDelegate alloc] init];
    [application setDelegate:delegate];
    [delegate setApplicationListener:this];
    
    menu = createMenu();
    [application setMainMenu: menu];
    
    GetCurrentProcess(&psn);
    TransformProcessType(&psn, kProcessTransformToForegroundApplication);
}

void Ggl::WindowCocoa::doCreateWindow() throw(std::exception) {
    
    NSUInteger style = createWindowStyle();
    NSRect rect;
    GglOpenGLView *view;
    NSOpenGLPixelFormatAttribute *attributes;
    NSOpenGLPixelFormat *pixelFormat;
    
    // Make window
    rect = NSMakeRect(0, 50, 512, 512);
    window = [[NSWindow alloc] initWithContentRect:rect
                               styleMask:style
                               backing:NSBackingStoreBuffered
                               defer:NO];
    
    // Make pixel format
    attributes = toArray(getWindowFormat());
    pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
    if (pixelFormat == nil) {
        throw Ggl::Exception("Could not make pixel format!");
    }
    delete[] attributes;
    
    // Make view
    rect = NSMakeRect(1.0, 1.0, 1.0, 1.0);
    view = [[GglOpenGLView alloc] initWithFrame:rect pixelFormat:pixelFormat];
    [view setOpenGLViewListener:this];
    
    // Add the view to the window
    [window setContentView:view];
    [window makeFirstResponder:view];
}

void Ggl::WindowCocoa::doCreateContext() throw(std::exception) {
    ;
}

void Ggl::WindowCocoa::doDestroyConnection() {
    ;
}

void Ggl::WindowCocoa::doDestroyContext() {
    ;
}

void Ggl::WindowCocoa::doDestroyWindow() {
    ;
}

void Ggl::WindowCocoa::doFlush() {
    glFlush();
}

void Ggl::WindowCocoa::doRun() {
    [pool drain];
    [application run];
}

void Ggl::WindowCocoa::doClose() {
    [application terminate:nil];
}

void Ggl::WindowCocoa::onApplicationTerminate() {
    fireDestroyEvent();
}

void Ggl::WindowCocoa::onOpenGLViewInit() {
    fireInitEvent();
}

void Ggl::WindowCocoa::onOpenGLViewDisplay() {
    fireDisplayEvent();
}

void Ggl::WindowCocoa::onOpenGLViewKey(int key) {
    fireKeyEvent(key);
}

void Ggl::WindowCocoa::onOpenGLViewDestroy() {
    ;
}

//----------------------------------------
// Helpers
//

NSUInteger Ggl::WindowCocoa::createWindowStyle() {
    return NSTitledWindowMask |
           NSClosableWindowMask |
           NSMiniaturizableWindowMask |
           NSResizableWindowMask;
}

NSMenu* Ggl::WindowCocoa::createMenu() {
    
    NSMenu *menu = createEmptyMenu();
    NSMenuItem *item = createEmptyMenuItem();
    NSMenu *submenu;
    
    submenu = createAppleMenu();
    [item setSubmenu: submenu];
    [menu addItem: item];
    
    return menu;
}

NSMenuItem* Ggl::WindowCocoa::createAppleMenuQuitItem() {
    
    NSMenuItem *item = [NSMenuItem alloc];
    
    [item initWithTitle:@"Quit"
          action:@selector(terminate:)
          keyEquivalent:@"q"];
    return item;
}

NSMenu* Ggl::WindowCocoa::createAppleMenu() {
    
    NSMenu *menu = createEmptyMenu();
    NSMenuItem *item = createAppleMenuQuitItem();
    
    [menu addItem: item];
    return menu;
}

NSMenu* Ggl::WindowCocoa::createEmptyMenu() {
    
    NSMenu *menu = [NSMenu alloc];
    
    [menu initWithTitle:@""];
    return menu;
}

NSMenuItem* Ggl::WindowCocoa::createEmptyMenuItem() {
    
    NSMenuItem *item = [NSMenuItem alloc];
    
    [item initWithTitle:@"" action:nil keyEquivalent:@""];
    return item;
}

/**
 * Converts a window format to an attributes array.
 * 
 * @param wf Configuration of window
 * @return New array of attributes, which should be freed
 */
GLuint*
Ggl::WindowCocoa::toArray(const WindowFormat &wf) {
    
    NSOpenGLPixelFormatAttribute *array;
    std::list<GLuint> attributes = toList(wf);
    std::list<GLuint>::iterator ai;
    int length = attributes.size() + 1;
    int count = 0;
    
    // Make array
    array = new NSOpenGLPixelFormatAttribute[length];
    for (ai=attributes.begin(); ai!=attributes.end(); ++ai) {
        array[count] = (*ai);
        ++count;
    }
    array[count] = nil;
    
    return array;
}

/**
 * Converts a window format to an attributes list.
 * 
 * @param wf Configuration of window
 * @return List of attributes
 */
std::list<GLuint>
Ggl::WindowCocoa::toList(const WindowFormat &wf) {
    
    std::list<GLuint> attributes;
    
    // Add default attributes
    attributes.push_back(NSOpenGLPFAAccelerated);
    
    // Profile and version
    attributes.push_back(NSOpenGLPFAOpenGLProfile);
    if (wf.isOpenGLCoreProfile()) {
        if (wf.isOpenGLVersion(3, 2)) {
            attributes.push_back(NSOpenGLProfileVersion3_2Core);
        } else {
            throw Ggl::Exception("Core profile only supported with OpenGL 3.2!");
        }
    } else {
        if (wf.isOpenGLVersion(2, 1)) {
            attributes.push_back(NSOpenGLProfileVersionLegacy);
        } else {
            throw Ggl::Exception("Legacy profile should use OpenGL 2.1!");
        }
    }
    
    // Pixel sizes
    attributes.push_back(NSOpenGLPFAColorSize);
    attributes.push_back(wf.getColorSize());
    attributes.push_back(NSOpenGLPFAAlphaSize);
    attributes.push_back(wf.getAlphaSize());
    attributes.push_back(NSOpenGLPFADepthSize);
    attributes.push_back(wf.getDepthSize());
    
    return attributes;
}

//----------------------------------------
// Objective C
//

@implementation GglApplicationDelegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)app {
    return YES;
}

- (void)applicationWillTerminate:(NSNotification*)notification {
    applicationListener->onApplicationTerminate();
}

- (void)setApplicationListener:(Ggl::ApplicationListener*)listener {
    applicationListener = listener;
}
@end

@implementation GglOpenGLView
- (void)keyDown:(NSEvent*)event {
    
    int c = [[event characters] characterAtIndex:0];
    
    openGLViewListener->onOpenGLViewKey(c);
}

- (void)drawRect:(NSRect)dirtyRect {
    openGLViewListener->onOpenGLViewDisplay();
}

- (void)prepareOpenGL {
    openGLViewListener->onOpenGLViewInit();
}

- (void)setOpenGLViewListener:(Ggl::OpenGLViewListener*)listener {
    openGLViewListener = listener;
}
@end
