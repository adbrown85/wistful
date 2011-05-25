/*
 * GglWindowCocoa.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowCocoa.hpp"

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
 * Creates the window.
 */
GglWindowCocoa::GglWindowCocoa() {
    pool = NULL;
    application = NULL;
    window = NULL;
}

/**
 * Destroys the window.
 */
GglWindowCocoa::~GglWindowCocoa() {
    ;
}

void GglWindowCocoa::doActivateContext() {
    cerr << "GglWindowCocoa::doActivateContext()" << endl;
}

void GglWindowCocoa::doActivateWindow() {
    cerr << "GglWindowCocoa::doActivateWindow()" << endl;
    
    [window makeKeyAndOrderFront:nil];
    [application activateIgnoringOtherApps:YES];
}

void GglWindowCocoa::doCreateConnection() throw(GglException) {
    cerr << "GglWindowCocoa::doCreateConnection()" << endl;
    
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
    cerr << "GglWindowCocoa::doCreateWindow()" << endl;
    
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
    cerr << "GglWindowCocoa::doCreateContext()" << endl;
}

void GglWindowCocoa::doDestroyConnection() {
    cerr << "GglWindowCocoa::doDestroyConnection()" << endl;
}

void GglWindowCocoa::doDestroyContext() {
    cerr << "GglWindowCocoa::doDestroyContext()" << endl;
}

void GglWindowCocoa::doDestroyWindow() {
    cerr << "GglWindowCocoa::doDestroyWindow()" << endl;
}

void GglWindowCocoa::doFlush() {
    cerr << "GglWindowCocoa::doFlush()" << endl;
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
NSOpenGLPixelFormatAttribute*
GglWindowCocoa::toArray(const GglWindowFormat &wf) {
    
    NSOpenGLPixelFormatAttribute *array;
    list<NSOpenGLPixelFormatAttribute> attributes;
    list<NSOpenGLPixelFormatAttribute>::iterator ai;
    int length;
    int count;
    
    // Add attributes
    attributes.push_back(NSOpenGLPFAAccelerated);
    attributes.push_back(NSOpenGLPFAOpenGLProfile);
    attributes.push_back(NSOpenGLProfileVersion3_2Core);
    attributes.push_back(NSOpenGLPFAColorSize);
    attributes.push_back(24);
    
    // Make array
    length = attributes.size() + 1;
    array = new NSOpenGLPixelFormatAttribute[length];
    count = 0;
    for (ai=attributes.begin(); ai!=attributes.end(); ++ai) {
        array[count] = (*ai);
        ++count;
    }
    array[count] = nil;
    
    return array;
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
