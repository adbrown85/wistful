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
	delete display;
}

/** Returns all available OpenGL configurations. */
list<GglConfig> GglConfigFactory::create() {
	
	int len;
	GLXFBConfig *fbcs = glXGetFBConfigs(display, 0, &len);
	list<GglConfig> glcs = toGglConfig(fbcs, len, display);
	
	XFree(fbcs);
	return glcs;
}

/** Returns OpenGL configurations meeting certain requirements. */
list<GglConfig> GglConfigFactory::create(const map<int,int> requirements) {
	
	const int *reqs = toArray(requirements);
	int len;
	GLXFBConfig *fbcs = glXChooseFBConfig(display, 0, reqs, &len);
	list<GlConfig> glcs = toGlConfig(fbcs, len, display);
	
	delete[] reqs;
	XFree(fbcs);
	return glcs;
}

//---------------------------------------------------------
// Helpers
//

/** Returns pointer to the default X display. */
Display* GglConfig::createDisplay() {
	return XOpenDisplay(const_cast<const char*>(getenv("DISPLAY")));
}

/** Converts a map of integers to an array.
 * 
 * @param m Map of integers to integers
 * @return Pointer to NULL-terminated array
 */
const int* GglConfig::toArray(const map<int,int> &m) {
	
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

/** Converts X framebuffer configurations to GL configurations.
 * 
 * @param arr Pointer to an array of X framebuffer configurations
 * @param len Length of the array
 * @param display Associated X display
 * @return List of GL configurations
 */
list<GglConfig> GglConfig::toGlConfig(GLXFBConfig *arr,
		                             int len,
		                             Display *display) {
	
	list<GglConfig> glcs;
	
	for (int i=0; i<len; ++i) {
		glcs.push_back(GglConfig(arr[i], display));
	}
	return glcs;
}

