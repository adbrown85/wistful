/*
 * GlConfig.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLCONFIG_HPP
#define GLCONFIG_HPP
#include "common.h"


/** Settings for how an OpenGL window is configured. */
class GlConfig {
public:
	GlConfig(GLXFBConfig fbc, Display);
	virtual ~GlConfig();
	virtual int getBufferSize() const;
	virtual bool isDoubleBuffered() const;
private:
	GLXFBConfig fbConfig;
};

#endif
