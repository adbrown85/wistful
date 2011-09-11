/*
 * common.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_COMMON_H
#define GGL_COMMON_H
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#ifdef __APPLE__
#define GL3_PROTOTYPES
#include <OpenGL/gl3.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>
#endif
#include <edo/Exception.hpp>

/**
 * @defgroup geometry
 * @defgroup image
 * @defgroup math
 * @defgroup shader
 * @defgroup system
 * @defgroup testing
 * @defgroup texture
 * @defgroup transform
 * @defgroup window
 */

#endif
