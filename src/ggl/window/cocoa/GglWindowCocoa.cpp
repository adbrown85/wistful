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
GglWindowCocoa::GglWindowCocoa(const GglWindowFormat &wf) : GglWindow(wf) {
    this->pool = NULL;
    this->application = NULL;
    this->window = NULL;
}

/**
 * Destroys the window.
 */
GglWindowCocoa::~GglWindowCocoa() {
    ;
}

void GglWindowCocoa::doActivateContext() {
    std::cerr << "GglWindowCocoa::doActivateContext()" << std::endl;
}

void GglWindowCocoa::doActivateWindow() {
    std::cerr << "GglWindowCocoa::doActivateWindow()" << std::endl;
    
    [window makeKeyAndOrderFront:nil];
    [application activateIgnoringOtherApps:YES];
}

void GglWindowCocoa::doCreateConnection() throw(GglException) {
    std::cerr << "GglWindowCocoa::doCreateConnection()" << std::endl;
    
    MyApplicationDelegate *delegate;
    NSMenu *menu;
    ProcessSerialNumber psn;
    
    pool = [[NSAutoreleasePool alloc] init];
    application = [NSApplication sharedApplication];
    
    delegate = [[MyApplicationDelegate alloc] init];
    [application setDelegate:delegate];
    
    menu = createMenu();
    [application setMainMenu: menu];
    
    GetCurrentProcess(&psn);
    TransformProcessType(&psn, kProcessTransformToForegroundApplication);
}

void GglWindowCocoa::doCreateWindow() throw(GglException) {
    std::cerr << "GglWindowCocoa::doCreateWindow()" << std::endl;
    
    NSUInteger style = createWindowStyle();
    NSRect rect;
    MyOpenGLView *view;
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
        throw GglException("Could not make pixel format!");
    }
    delete[] attributes;
    
    // Make view
    rect = NSMakeRect(1.0, 1.0, 1.0, 1.0);
    view = [[MyOpenGLView alloc] initWithFrame:rect pixelFormat:pixelFormat];
    [view setWindowListener:this];
    
    // Add the view to the window
    [window setContentView:view];
    [window makeFirstResponder:view];
}

void GglWindowCocoa::doCreateContext() throw(GglException) {
    std::cerr << "GglWindowCocoa::doCreateContext()" << std::endl;
}

void GglWindowCocoa::doDestroyConnection() {
    std::cerr << "GglWindowCocoa::doDestroyConnection()" << std::endl;
}

void GglWindowCocoa::doDestroyContext() {
    std::cerr << "GglWindowCocoa::doDestroyContext()" << std::endl;
}

void GglWindowCocoa::doDestroyWindow() {
    std::cerr << "GglWindowCocoa::doDestroyWindow()" << std::endl;
}

void GglWindowCocoa::doFlush() {
    std::cerr << "GglWindowCocoa::doFlush()" << std::endl;
    glFlush();
}

void GglWindowCocoa::doRun() {
    [pool drain];
    [application run];
}

void GglWindowCocoa::onInit(GglWindow *window) {
    ;
}

void GglWindowCocoa::onDisplay(GglWindow *window) {
    fireDisplayEvent();
}

void GglWindowCocoa::onKey(GglWindow *window, GglWindowEvent &event) {
    ;
}

void GglWindowCocoa::onDestroy(GglWindow *window) {
    ;
}

//----------------------------------------
// Helpers
//

NSUInteger GglWindowCocoa::createWindowStyle() {
    return NSTitledWindowMask |
           NSClosableWindowMask |
           NSMiniaturizableWindowMask |
           NSResizableWindowMask;
}

NSMenu* GglWindowCocoa::createMenu() {
    
    NSMenu *menu = createEmptyMenu();
    NSMenuItem *item = createEmptyMenuItem();
    NSMenu *submenu;
    
    submenu = createAppleMenu();
    [item setSubmenu: submenu];
    [menu addItem: item];
    
    return menu;
}

NSMenuItem* GglWindowCocoa::createAppleMenuQuitItem() {
    
    NSMenuItem *item = [NSMenuItem alloc];
    
    [item initWithTitle:@"Quit"
          action:@selector(terminate:)
          keyEquivalent:@"q"];
    return item;
}

NSMenu* GglWindowCocoa::createAppleMenu() {
    
    NSMenu *menu = createEmptyMenu();
    NSMenuItem *item = createAppleMenuQuitItem();
    
    [menu addItem: item];
    return menu;
}

NSMenu* GglWindowCocoa::createEmptyMenu() {
    
    NSMenu *menu = [NSMenu alloc];
    
    [menu initWithTitle:@""];
    return menu;
}

NSMenuItem* GglWindowCocoa::createEmptyMenuItem() {
    
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
GglWindowCocoa::toArray(const GglWindowFormat &wf) {
    
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
GglWindowCocoa::toList(const GglWindowFormat &wf) {
    
    std::list<GLuint> attributes;
    
    // Add default attributes
    attributes.push_back(NSOpenGLPFAAccelerated);
    
    // Profile and version
    attributes.push_back(NSOpenGLPFAOpenGLProfile);
    if (wf.isOpenGLProfile(GGL_CORE_PROFILE)) {
        if (wf.isOpenGLVersion(3, 2)) {
            attributes.push_back(NSOpenGLProfileVersion3_2Core);
        } else {
            throw GglException("Core profile only supported with OpenGL 3.2!");
        }
    } else {
        if (wf.isOpenGLVersion(2, 1)) {
            attributes.push_back(NSOpenGLProfileVersionLegacy);
        } else {
            throw GglException("Legacy profile should use OpenGL 2.1!");
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

@implementation MyApplicationDelegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)app {
    return YES;
}
@end

@implementation MyOpenGLView
- (void)keyDown:(NSEvent*)event {
    ;
}

- (void)drawRect:(NSRect)dirtyRect {
    windowListener->onDisplay(NULL);
}

- (void)setWindowListener:(GglWindowListener*)listener {
    windowListener = listener;
}
@end