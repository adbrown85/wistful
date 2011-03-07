/*
 * GglConfig.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfig.hpp"

/** Creates an OpenGL configuration builder. */
GglConfigBuilder::GglConfigBuilder() {
	red = 0;
	green = 0;
	blue = 0;
	alpha = 0;
	depth = 0;
	doubleBuffered = false;
}

/** Creates an OpenGL configuration. */
GglConfig::GglConfig(GglConfigBuilder *b) {
	this->red = b->red;
	this->green = b->green;
	this->blue = b->blue;
	this->alpha = b->alpha;
	this->depth = b->depth;
	this->stencil = b->stencil;
	this->doubleBuffered = b->doubleBuffered;
}

/** Returns size of red buffer in bits. */
int GglConfig::getRedSize() const {
	return red;
}

/** Returns size of green buffer in bits. */
int GglConfig::getGreenSize() const {
	return green;
}

/** Returns size of red buffer in bits. */
int GglConfig::getBlueSize() const {
	return blue;
}

/** Returns size of red buffer in bits. */
int GglConfig::getAlphaSize() const {
	return alpha;
}

/** Returns size of depth buffer in bits. */
int GglConfig::getDepthSize() const {
	return depth;
}

/** Returns size of stencil buffer in bits. */
int GglConfig::getStencilSize() const {
	return stencil;
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
