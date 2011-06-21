/*
 * ConfigFactoryGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/glx/ConfigFactoryGlx.hpp"
using namespace Ggl;
using namespace std;

/**
 * Creates an OpenGL configuration factory.
 */
ConfigFactoryGlx::ConfigFactoryGlx() {
    display = createDisplay();
}

/**
 * Destroys the factory.
 */
ConfigFactoryGlx::~ConfigFactoryGlx() {
    XCloseDisplay(display);
}

/**
 * Returns OpenGL configuration matching a window format.
 * 
 * @param wf Container with window settings
 */
GLXFBConfig ConfigFactoryGlx::create(const WindowFormat &wf) {
    
    map<int,int> m;
    int colorComponentSize = wf.getColorSize() / 8;
    
    m[GLX_X_RENDERABLE] = 1;
    m[GLX_DRAWABLE_TYPE] = GLX_WINDOW_BIT;
    m[GLX_RENDER_TYPE] = GLX_RGBA_BIT;
    m[GLX_CONFIG_CAVEAT] = GLX_NONE;
    m[GLX_DOUBLEBUFFER] = 1;
    m[GLX_RED_SIZE] = colorComponentSize;
    m[GLX_GREEN_SIZE] = colorComponentSize;
    m[GLX_BLUE_SIZE] = colorComponentSize;
    m[GLX_ALPHA_SIZE] = wf.getAlphaSize();
    m[GLX_DEPTH_SIZE] = wf.getDepthSize();
    
    return create(m);
}

/**
 * Returns OpenGL configurations meeting certain requirements.
 */
GLXFBConfig
ConfigFactoryGlx::create(const map<int,int> &requirements) {
    
    const int *reqs = toArray(requirements);
    int len;
    GLXFBConfig *fbcs = glXChooseFBConfig(display, 0, reqs, &len);
    GLXFBConfig config;
    
    // Validate
    if (len == 0) {
        throw Exception("No configuration found for requirements!");
    }
    
    // Copy the first config
    config = fbcs[0];
    
    // Clean up
    delete[] reqs;
    XFree(fbcs);
    
    return config;
}

//---------------------------------------------------------
// Helpers
//

/**
 * Returns pointer to the default X display.
 */
Display* ConfigFactoryGlx::createDisplay() {
    return XOpenDisplay(NULL);
}

/**
 * Converts a map of integers to an array.
 * 
 * @param m Map of integers to integers
 * @return Pointer to NULL-terminated array
 */
const int* ConfigFactoryGlx::toArray(const map<int,int> &m) {
    
    int len = (m.size() * 2) + 1;           // Length of array
    int *arr = new int[len];                // Array of integers
    map<int,int>::const_iterator it;        // Iterator over map
    int i = 0;                              // Index into array
    
    for (it=m.begin(); it!=m.end(); ++it) {
        arr[i++] = it->first;
        arr[i++] = it->second;
    }
    arr[i] = (int) NULL;
    return const_cast<const int*>(arr);
}
