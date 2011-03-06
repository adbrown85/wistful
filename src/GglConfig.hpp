/*
 * GglConfig.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIG_HPP
#define GGLCONFIG_HPP
#include "common.h"


/** Settings for how an OpenGL window is configured. */
class GglConfig {
public:
	GglConfig(GLXFBConfig fbc);
	virtual ~GglConfig();
	virtual int getBufferSize() const;
	virtual bool isDoubleBuffered() const;
private:
	GLXFBConfig fbConfig;
};

#endif
