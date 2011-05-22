/*
 * GglWindowCocoa.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowCocoa.hpp"

/**
 * Creates the window.
 */
GglWindowCocoa::GglWindowCocoa() {
    pool = NULL;
    application = NULL;
    delegate = NULL;
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
    
    ProcessSerialNumber psn;
    
    pool = [[NSAutoreleasePool alloc] init];
    application = [NSApplication sharedApplication];
    delegate = [[MyApplicationDelegate alloc] init];
    
    [application setDelegate:delegate];
    
    GetCurrentProcess(&psn);
    TransformProcessType(&psn, kProcessTransformToForegroundApplication);
}

void GglWindowCocoa::doCreateWindow() throw(GglException) {
    cerr << "GglWindowCocoa::doCreateWindow()" << endl;
    
    NSRect rect = NSMakeRect(0, 50, 512, 512);
    NSUInteger style = createWindowStyle();
    
    window = [[NSWindow alloc] initWithContentRect:rect
                               styleMask:style
                               backing:NSBackingStoreBuffered
                               defer:NO];
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
}

GglEvent GglWindowCocoa::doGetEvent() {
    return GglEvent(OTHER);
}

void GglWindowCocoa::doRun() {
    [pool drain];
    [application run];
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

@implementation MyApplicationDelegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)app {
    return YES;
}
@end
