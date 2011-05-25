/*
 * GglWindowFormat.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWFORMAT_HPP
#define GGLWINDOWFORMAT_HPP
#include "ggl_common.h"
#include "GglException.hpp"


/*
 * OpenGL profile for a window. 
 */
enum GglOpenGLProfile {
    GGL_CORE_PROFILE,
    GGL_COMPATIBILITY_PROFILE
};


/**
 * Container for settings describing a window configuration.
 */
class GglWindowFormat {
public:
    GglWindowFormat();
    virtual ~GglWindowFormat();
// Accessors and mutators
    int getColorSize() const;
    void setColorSize(int bits);
    int getAlphaSize() const;
    void setAlphaSize(int bits);
    int getDepthSize() const;
    void setDepthSize(int bits);
    int getOpenGLMajorVersion() const;
    int getOpenGLMinorVersion() const;
    void setOpenGLVersion(int major, int minor);
    bool isOpenGLVersion(int major, int minor) const;
    GglOpenGLProfile getOpenGLProfile() const;
    void setOpenGLProfile(GglOpenGLProfile profile);
    bool isOpenGLProfile(GglOpenGLProfile profile) const;
private:
    int colorSize;
    int alphaSize;
    int depthSize;
    int majorVersion;
    int minorVersion;
    GglOpenGLProfile profile;
// Constants
    static const int DEFAULT_COLOR_SIZE = 24;
    static const int DEFAULT_ALPHA_SIZE = 8;
    static const int DEFAULT_DEPTH_SIZE = 16;
    static const int DEFAULT_MAJOR_VERSION = 3;
    static const int DEFAULT_MINOR_VERSION = 2;
};

#endif
