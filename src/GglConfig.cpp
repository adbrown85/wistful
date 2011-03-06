/*
 * GglConfig.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfig.hpp"

/** Creates an OpenGL configuration. */
GglConfig::GglConfig(GLXFBConfig fbc) {
	this->fbConfig = fbc;
}

/** Destroys an OpenGL configuration. */
GglConfig::~GglConfig() {
	
}

int GglConfig::getBufferSize() const {
	return findAttribute(GLX_BUFFER_SIZE);
}

bool GglConfig::isDoubleBuffered() const {
	return findAttribute(GLX_DOUBLEBUFFER) > 0;
}

/** Returns value of an attribute. */
int GglConfig::findAttribute(int name) const {
	
	int value;
	
	glXGetFBConfigAttrib(display, fbConfig, name, &value);
	return value;
}
