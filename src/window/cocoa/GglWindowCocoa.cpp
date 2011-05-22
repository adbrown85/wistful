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
    ;
}

/**
 * Destroys the window.
 */
GglWindowCocoa::~GglWindowCocoa() {
    ;
}

void GglWindowCocoa::doActivateContext() {
    cout << "GglWindowCocoa::doActivateContext()" << endl;
}

void GglWindowCocoa::doActivateWindow() {
    cout << "GglWindowCocoa::doActivateWindow()" << endl;
}

void GglWindowCocoa::doCreateConnection() throw(GglException) {
    cout << "GglWindowCocoa::doCreateConnection()" << endl;
}

void GglWindowCocoa::doCreateWindow() throw(GglException) {
    cout << "GglWindowCocoa::doCreateWindow()" << endl;
}

void GglWindowCocoa::doCreateContext() throw(GglException) {
    cout << "GglWindowCocoa::doCreateContext()" << endl;
}

void GglWindowCocoa::doDestroyConnection() {
    cout << "GglWindowCocoa::doDestroyConnection()" << endl;
}

void GglWindowCocoa::doDestroyContext() {
    cout << "GglWindowCocoa::doDestroyContext()" << endl;
}

void GglWindowCocoa::doDestroyWindow() {
    cout << "GglWindowCocoa::doDestroyWindow()" << endl;
}

void GglWindowCocoa::doFlush() {
    cout << "GglWindowCocoa::doFlush()" << endl;
}

GglEvent GglWindowCocoa::doGetEvent() {
    return GglEvent(OTHER);
}

void GglWindowCocoa::doRun() {
    cout << "GglWindowCocoa::doRun()" << endl;
}
