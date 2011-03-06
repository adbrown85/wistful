/*
 * GlConfig.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GlConfig.hpp"

/** Creates an OpenGL configuration. */
GlConfig::GlConfig(GLXFBConfig fbc) {
	this->fbConfig = fbc;
}

/** Destroys an OpenGL configuration. */
GlConfig::~GlConfig() {
	
}

int GlConfig::getBufferSize() const {
	return findAttribute(GLX_BUFFER_SIZE);
}

bool GlConfig::isDoubleBuffered() const {
	return findAttribute(GLX_DOUBLEBUFFER) > 0;
}

/** Returns value of an attribute. */
int GlConfig::findAttribute(int name) const {
	
	int value;
	
	glXGetFBConfigAttrib(display, fbConfig, name, &value);
	return value;
}
