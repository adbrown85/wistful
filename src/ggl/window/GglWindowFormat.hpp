/*
 * GglWindowFormat.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLWINDOWFORMAT_HPP
#define GGLWINDOWFORMAT_HPP
#include "ggl/common.h"
#include "ggl/GglException.hpp"


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
    bool isOpenGLCoreProfile() const;
    void setOpenGLCoreProfile(bool coreProfile);
private:
    int colorSize;
    int alphaSize;
    int depthSize;
    int majorVersion;
    int minorVersion;
    bool coreProfile;
// Constants
    static const int DEFAULT_COLOR_SIZE = 24;
    static const int DEFAULT_ALPHA_SIZE = 8;
    static const int DEFAULT_DEPTH_SIZE = 16;
    static const int DEFAULT_MAJOR_VERSION = 3;
    static const int DEFAULT_MINOR_VERSION = 2;
    static const bool DEFAULT_CORE_PROFILE = true;
};

#endif
