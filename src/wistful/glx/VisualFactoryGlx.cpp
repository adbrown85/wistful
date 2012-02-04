/*
 * VisualFactoryGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "wistful/glx/VisualFactoryGlx.hpp"
using namespace Wistful;
using namespace std;

VisualFactoryGlx::VisualFactoryGlx() {
    display = createDisplay();
}

VisualFactoryGlx::~VisualFactoryGlx() {
    XCloseDisplay(display);
}

XVisualInfo*
VisualFactoryGlx::createVisualInfo(const WindowFormat &wf) {
 
    int *attributes = toArray(wf);

    return glXChooseVisual(display, 0, attributes);
}

//----------------------------------------
// Helpers
//

Display*
VisualFactoryGlx::createDisplay() throw(exception) {
    
    Display *display = XOpenDisplay(NULL);
    
    if (display == NULL) {
        throw Exception("Could not create display!");
    }
    return display;
}

int*
VisualFactoryGlx::toArray(const WindowFormat &wf) {
 
    list<int> attributes = toList(wf);
    list<int>::iterator li;
    int len = attributes.size() + 1;
    int *arr;
    int i;
 
    // Allocate
    arr = new int[len];
    arr[len - 1] = NULL;

    // Fill
    i = 0;
    for (li=attributes.begin(); li!=attributes.end(); ++li) {
        arr[i] = (*li);
        ++i;
    }

    return arr;
}

list<int>
VisualFactoryGlx::toList(const WindowFormat &wf) {
 
    list<int> L;
    int colorComponentSize = wf.getColorSize() / 8;
 
    L.push_back(GLX_RGBA);
    L.push_back(GLX_DOUBLEBUFFER);
    L.push_back(GLX_RED_SIZE);
    L.push_back(colorComponentSize);
    L.push_back(GLX_GREEN_SIZE);
    L.push_back(colorComponentSize);
    L.push_back(GLX_BLUE_SIZE);
    L.push_back(colorComponentSize);
    L.push_back(GLX_ALPHA_SIZE);
    L.push_back(wf.getAlphaSize());
    L.push_back(GLX_DEPTH_SIZE);
    L.push_back(wf.getDepthSize());

    return L;
}

