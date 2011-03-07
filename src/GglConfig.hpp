/*
 * GglConfig.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIG_HPP
#define GGLCONFIG_HPP
#include "common.h"


/** @brief <i>Builder</i> for @GglConfig. */
class GglConfigBuilder {
public:
	GglConfigBuilder();
	virtual ~GglConfigBuilder() {}
	virtual void reset();
// Getters and setters
	virtual int getRedSize();
	virtual void setRedSize(int r);
	virtual int getGreenSize();
	virtual void setGreenSize(int g);
	virtual int getBlueSize();
	virtual void setBlueSize(int b);
	virtual int getAlphaSize();
	virtual void setAlphaSize(int a);
private:
	int r;                                  // Red size
	int g;                                  // Green size
	int b;                                  // Blue size
	int a;                                  // Alpha size
// Constants
	static const int DEFAULT_R = 8;
	static const int DEFAULT_G = 8;
	static const int DEFAULT_B = 8;
	static const int DEFAULT_A = 8;
};


/** @brief OpenGL configuration. */
class GglConfig {
public:
	GglConfig(GglConfigBuilder *b);
	virtual ~GglConfig() {}
	virtual int getRedSize() const;
	virtual int getGreenSize() const;
	virtual int getBlueSize() const;
	virtual int getAlphaSize() const;
private:
	int r;                                  // Red size
	int g;                                  // Green size
	int b;                                  // Blue size
	int a;                                  // Alpha size
};


/** @brief <i>Builder</i> for @GglConfigGlx. */
class GglConfigGlxBuilder : public GglConfigBuilder {
public:
	virtual ~GglConfigGlxBuilder() {}
// Getters and setters
	virtual GLXFBConfig getFBConfig();
	virtual void setFBConfig(GLXFBConfig fbc);
private:
	GLXFBConfig glxFBConfig;                // GLX Framebuffer configuration
};


/** @brief OpenGL configuration with GLX. */
class GglConfigGlx : public GglConfig {
public:
	GglConfigGlx(GglConfigGlxBuilder *b);
	virtual ~GglConfigGlx() {}
	virtual GLXFBConfig getFBConfig();
private:
	GLXFBConfig glxFBConfig;                // GLX Framebuffer configuration
};


#endif
