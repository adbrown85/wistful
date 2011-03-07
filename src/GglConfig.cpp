/*
 * GglConfig.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfig.hpp"

/** Creates an OpenGL configuration builder. */
GglConfigBuilder::GglConfigBuilder() {
	r = 0;
	g = 0;
	b = 0;
	a = 0;
	depth = 0;
	doubleBuffered = false;
}

/** Creates an OpenGL configuration. */
GglConfig::GglConfig(GglConfigBuilder *b) {
	this->r = b->r;
	this->g = b->g;
	this->b = b->b;
	this->a = b->a;
	this->depth = b->depth;
	this->doubleBuffered = b->doubleBuffered;
}

/** Returns size of red buffer in bits. */
int GglConfig::getRedSize() const {
	return r;
}

/** Returns size of green buffer in bits. */
int GglConfig::getGreenSize() const {
	return g;
}

/** Returns size of red buffer in bits. */
int GglConfig::getBlueSize() const {
	return b;
}

/** Returns size of red buffer in bits. */
int GglConfig::getAlphaSize() const {
	return a;
}

/** Returns size of depth buffer in bits. */
int GglConfig::getDepthSize() const {
	return depth;
}

/** Returns <tt>true</tt> if has both front and back buffers. */
bool GglConfig::isDoubleBuffered() const {
	return doubleBuffered;
}

/** Creates an OpenGL configuration with GLX. */
GglConfigGlx::GglConfigGlx(GglConfigGlxBuilder *b) : GglConfig(b) {
	this->glxFBConfig = b->glxFBConfig;
}

/** Returns native framebuffer configuration for GLX. */
GLXFBConfig GglConfigGlx::getFBConfig() {
	return glxFBConfig;
}
