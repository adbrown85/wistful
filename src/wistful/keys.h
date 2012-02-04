/*
 * wistful_keys.h
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_KEYS_H_
#define WISTFUL_KEYS_H_
#include "wistful/common.h"

#if defined(HAVE_COCOA)
#include "wistful/cocoa/keys_cocoa.h"
#elif defined(HAVE_GLX)
#include "wistful/glx/keys_glx.h"
#endif


#endif
