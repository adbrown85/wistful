/*
 * ggl_keys.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_KEYS_H_
#define GGL_KEYS_H_
#include "ggl/common.h"

#if defined(HAVE_COCOA)
#include "ggl/window/cocoa/keys_cocoa.h"
#elif defined(HAVE_GLX)
#include "ggl/window/glx/keys_glx.h"
#endif


#endif
