/*
 * GglConfigFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLCONFIGFACTORY_HPP
#define GGLCONFIGFACTORY_HPP
#include "common.h"
#include "GglConfig.hpp"


/** Utility for creating OpenGL configurations. */
class GglConfigFactory {
public:
	GglConfigFactory();
	virtual ~GglConfigFactory();
	virtual list<GglConfig> create();
	virtual list<GglConfig> create(const map<int,int> &requirements);
private:
	Display *display;
// Helpers
	static Display* createDisplay();
	static const int* toArray(const map<int,int> &m);
	static list<GglConfig> toGglConfig(GLXFBConfig*, int, Display*);
};

#endif
