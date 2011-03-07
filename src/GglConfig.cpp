/*
 * GglConfig.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfig.hpp"

/** Creates an OpenGL configuration builder. */
GglConfigBuilder::GglConfigBuilder() {
	r = DEFAULT_R;
	g = DEFAULT_G;
	b = DEFAULT_B;
	a = DEFAULT_A;
	depth = DEFAULT_DEPTH;
}

/** Reverts all values to their defaults. */
void GglConfigBuilder::reset() {
	r = DEFAULT_R;
	g = DEFAULT_G;
	b = DEFAULT_B;
	a = DEFAULT_A;
	depth = DEFAULT_DEPTH;
}

/** Returns size of red buffer in bits. */
int GglConfigBuilder::getRedSize() {
	return r;
}

/** Changes the size of the red buffer. */
void GglConfigBuilder::setRedSize(int r) {
	this->r = r;
}

/** Returns size of green buffer in bits. */
int GglConfigBuilder::getGreenSize() {
	return g;
}

/** Changes the size of the green buffer. */
void GglConfigBuilder::setGreenSize(int g) {
	this->g = g;
}

/** Returns size of red buffer in bits. */
int GglConfigBuilder::getBlueSize() {
	return b;
}

/** Changes the size of the blue buffer. */
void GglConfigBuilder::setBlueSize(int b) {
	this->b = b;
}

/** Returns size of red buffer in bits. */
int GglConfigBuilder::getAlphaSize() {
	return a;
}

/** Changes the size of the alpha buffer. */
void GglConfigBuilder::setAlphaSize(int a) {
	this->a = a;
}

/** Returns size of depth buffer in bits. */
int GglConfigBuilder::getDepthSize() {
	return depth;
}

/** Changes the size of the depth buffer. */
void GglConfigBuilder::setDepthSize(int depth) {
	this->depth = depth;
}

/** Creates an OpenGL configuration. */
GglConfig::GglConfig(GglConfigBuilder *b) {
	this->r = b->getRedSize();
	this->g = b->getGreenSize();
	this->b = b->getBlueSize();
	this->a = b->getAlphaSize();
	this->depth = b->getDepthSize();
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

/** Changes the native framebuffer configuration with GLX. */
void GglConfigGlxBuilder::setFBConfig(GLXFBConfig fbc) {
	this->glxFBConfig = fbc;
}

/** Returns native framebuffer configuration with GLX. */
GLXFBConfig GglConfigGlxBuilder::getFBConfig() {
	return glxFBConfig;
}

/** Creates an OpenGL configuration with GLX. */
GglConfigGlx::GglConfigGlx(GglConfigGlxBuilder *b) : GglConfig(b) {
	this->glxFBConfig = b->getFBConfig();
}

/** Returns native framebuffer configuration for GLX. */
GLXFBConfig GglConfigGlx::getFBConfig() {
	return glxFBConfig;
}
