/*
 * common.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_COMMON_H
#define WISTFUL_COMMON_H
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#ifdef __APPLE__
#define GL3_PROTOTYPES
#include <OpenGL/gl3.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>
#endif

#endif
