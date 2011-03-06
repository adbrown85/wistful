/*
 * GlConfigFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLCONFIGFACTORY_HPP
#define GLCONFIGFACTORY_HPP
#include "common.h"


/** Utility for creating OpenGL configurations. */
class GlConfigFactory {
public:
	GlConfigFactory();
	virtual ~GlConfigFactory();
	virtual list<GlConfig> create();
	virtual list<GlConfig> create(const map<int,int> &requirements);
private:
	Display *display;
// Helpers
	static Display* createDisplay();
	static const int* toArray(const map<int,int> &m);
	static list<GlConfig> toGlConfig(GLXFBConfig*, int, Display*);
};

#endif
