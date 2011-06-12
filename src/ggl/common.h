/*
 * common.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_COMMON_H
#define GGL_COMMON_H
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glx.h>
#endif
using namespace std;

//#ifdef HAVE_CONFIG_H
#include "ggl/config.h"
//#endif

#endif
