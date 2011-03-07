/*
 * GglConfigFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfigFactory.hpp"

/** Creates an OpenGL configuration factory. */
GglConfigFactory::GglConfigFactory() {
	display = createDisplay();
}

/** Destroys the factory. */
GglConfigFactory::~GglConfigFactory() {
//	delete display;
}

/** Returns OpenGL configurations meeting certain requirements. */
list<GglConfig*> GglConfigFactory::create(const map<int,int> &requirements) {
	
	const int *reqs = toArray(requirements);
	int len;
	GLXFBConfig *fbcs = glXChooseFBConfig(display, 0, reqs, &len);
	list<GglConfig*> configs;
	GglConfigGlxBuilder b;
	
	// Convert configurations
	for (int i=0; i<len; ++i) {
		b.setFBConfig(fbcs[i]);
		b.setRedSize(getValue(fbcs[i], GLX_RED_SIZE));
		b.setGreenSize(getValue(fbcs[i], GLX_GREEN_SIZE));
		b.setBlueSize(getValue(fbcs[i], GLX_BLUE_SIZE));
		b.setAlphaSize(getValue(fbcs[i], GLX_ALPHA_SIZE));
		b.setDepthSize(getValue(fbcs[i], GLX_DEPTH_SIZE));
		b.setDoubleBuffered(getValue(fbcs[i], GLX_DOUBLEBUFFER));
		configs.push_back(new GglConfigGlx(&b));
	}
	
	// Finish
	delete[] reqs;
	XFree(fbcs);
	return configs;
}

//---------------------------------------------------------
// Helpers
//

/** Returns pointer to the default X display. */
Display* GglConfigFactory::createDisplay() {
	return XOpenDisplay(const_cast<const char*>(getenv("DISPLAY")));
}

/** Converts a map of integers to an array.
 * 
 * @param m Map of integers to integers
 * @return Pointer to NULL-terminated array
 */
const int* GglConfigFactory::toArray(const map<int,int> &m) {
	
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
int GglConfigFactory::getValue(GLXFBConfig fbc, int key) {
	
	int value;
	
	glXGetFBConfigAttrib(display, fbc, key, &value);
	return value;
}

