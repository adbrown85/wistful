/*
 * GglConfigFactoryGlx.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfigFactoryGlx.hpp"

/** Creates an OpenGL configuration factory. */
GglConfigFactoryGlx::GglConfigFactoryGlx() {
#ifdef HAVE_GLX
    display = createDisplay();
#endif //HAVE_GLX
}

/** Destroys the factory. */
GglConfigFactoryGlx::~GglConfigFactoryGlx() {
#ifdef HAVE_GLX
    XCloseDisplay(display);
#endif //HAVE_GLX
}

/** Returns OpenGL configurations meeting certain requirements. */
GglConfig* GglConfigFactoryGlx::create(const map<int,int> &requirements) {
#ifdef HAVE_GLX
    const int *reqs = toArray(requirements);
    int len;
    GLXFBConfig *fbcs = glXChooseFBConfig(display, 0, reqs, &len);
    GglConfig *config;
    int id;
    
    // Validate
    if (len == 0) {
        throw GglException("No configuration found for requirements!");
    }
    
    // Convert configurations
    id = getValue(fbcs[0], GLX_FBCONFIG_ID);
    config = find(id);
    if (config == NULL) {
        config = doCreate(fbcs[0]);
        add(id, config);
    }
    
    // Finish
    delete[] reqs;
    XFree(fbcs);
    return config;
#else
    return NULL;
#endif
}

#ifdef HAVE_GLX

//---------------------------------------------------------
// Helpers
//

/** Returns pointer to the default X display. */
Display* GglConfigFactoryGlx::createDisplay() {
    return XOpenDisplay(NULL);
}

/** Actually creates a configuration. */
GglConfig* GglConfigFactoryGlx::doCreate(GLXFBConfig &fbc) {
    
    GglConfigGlxBuilder b;
    
    b.glxFBConfig = fbc;
    b.red = getValue(fbc, GLX_RED_SIZE);
    b.green = getValue(fbc, GLX_GREEN_SIZE);
    b.blue = getValue(fbc, GLX_BLUE_SIZE);
    b.alpha = getValue(fbc, GLX_ALPHA_SIZE);
    b.depth = getValue(fbc, GLX_DEPTH_SIZE);
    b.stencil = getValue(fbc, GLX_STENCIL_SIZE);
    b.doubleBuffered = getValue(fbc, GLX_DOUBLEBUFFER);
    b.id = getValue(fbc, GLX_FBCONFIG_ID);
    return new GglConfigGlx(&b);
}

/** Converts a map of integers to an array.
 * 
 * @param m Map of integers to integers
 * @return Pointer to NULL-terminated array
 */
const int* GglConfigFactoryGlx::toArray(const map<int,int> &m) {
    
    int len = (m.size() * 2) + 1;           // Length of array
    int *arr = new int[len];                // Array of integers
    map<int,int>::const_iterator it;        // Iterator over map
    int i = 0;                              // Index into array
    
    for (it=m.begin(); it!=m.end(); ++it) {
        arr[i++] = it->first;
        arr[i++] = it->second;
    }
    arr[i] = NULL;
    return const_cast<const int*>(arr);
}

/** Returns the value of an attribute.
 * 
 * @param display Current X screen
 * @param fbc GLX Framebuffer configuration
 * @param key Name of attribute
 */
int GglConfigFactoryGlx::getValue(GLXFBConfig fbc, int key) {
    
    int value;
    
    glXGetFBConfigAttrib(display, fbc, key, &value);
    return value;
}

#endif //HAVE_GLX
