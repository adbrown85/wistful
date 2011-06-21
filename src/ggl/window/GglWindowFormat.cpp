/*
 * GglWindowFormat.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/GglWindowFormat.hpp"

/**
 * Creates a default window format.
 */
Ggl::WindowFormat::WindowFormat() {
    colorSize = DEFAULT_COLOR_SIZE;
    alphaSize = DEFAULT_ALPHA_SIZE;
    depthSize = DEFAULT_DEPTH_SIZE;
    majorVersion = DEFAULT_MAJOR_VERSION;
    minorVersion = DEFAULT_MINOR_VERSION;
    coreProfile = DEFAULT_CORE_PROFILE;
}

/**
 * Destroys the window format.
 */
Ggl::WindowFormat::~WindowFormat() {
    ;
}

/**
 * Returns number of bits used for a pixel in the color buffer.
 */
int
Ggl::WindowFormat::getColorSize() const {
    return colorSize;
}

/**
 * Changes the number of bits used for a pixel in the color buffer.
 * 
 * @param colorSize Size of color buffer pixel in bits
 * @throw GglException if size is negative
 */
void
Ggl::WindowFormat::setColorSize(int colorSize) {
    if (colorSize < 0) {
        throw Exception("Color size is negative!");
    } else {
        this->colorSize = colorSize;
    }
}

/**
 * Returns number of bits used for a pixel's alpha component.
 */
int
Ggl::WindowFormat::getAlphaSize() const {
    return alphaSize;
}

/**
 * Changes number of bits used for a pixel's alpha component.
 * 
 * @param alphaSize Number of bits to store opacity
 * @throw GglException if size is negative
 */
void
Ggl::WindowFormat::setAlphaSize(int alphaSize) {
    if (alphaSize < 0) {
        throw Exception("Alpha size is negative!");
    } else {
        this->alphaSize = alphaSize;
    }
}

/**
 * Returns number of bits used for a pixel in the depth buffer.
 */
int
Ggl::WindowFormat::getDepthSize() const {
    return depthSize;
}

/**
 * Changes the number of bits used for a pixel in the depth buffer. 
 * 
 * @param depthSize Size of depth buffer pixel in bits
 * @throw GglException if size is negative
 */
void
Ggl::WindowFormat::setDepthSize(int depthSize) {
    if (depthSize < 0) {
        throw Exception("Depth size is negative!");
    } else {
        this->depthSize = depthSize;
    }
}

/**
 * Returns major version number of OpenGL.
 */
int
Ggl::WindowFormat::getOpenGLMajorVersion() const {
    return majorVersion;
}

/**
 * Returns minor version number of OpenGL.
 */
int
Ggl::WindowFormat::getOpenGLMinorVersion() const {
    return minorVersion;
}

/**
 * Changes the OpenGL version.
 * 
 * @param major Major OpenGL version number
 * @param minor Minor OpenGL version number
 * @throw GglException if major number less than 1
 * @throw GglException if minor number less than 0
 */
void
Ggl::WindowFormat::setOpenGLVersion(int major,
                                    int minor) {
    if (major < 1) {
        throw Exception("Major version less than 1!");
    } else if (minor < 0) {
        throw Exception("Minor version less than 0!");
    } else {
        this->majorVersion = major;
        this->minorVersion = minor;
    }
}

/**
 * Checks if an OpenGL version matches the format's version.
 * 
 * @param major OpenGL major version number
 * @param minor OpenGL minor version number
 * @return <tt>true</tt> if the versions match
 */
bool
Ggl::WindowFormat::isOpenGLVersion(int major,
                                   int minor) const {
    return (this->majorVersion == major) && (this->minorVersion == minor);
}

/**
 * Returns <tt>true</tt> if using OpenGL core profile.
 */
bool
Ggl::WindowFormat::isOpenGLCoreProfile() const {
    return coreProfile;
}

/**
 * Changes whether to use the OpenGL core profile.
 * 
 * @param coreProfile <tt>true</tt> to use the core profile
 */
void
Ggl::WindowFormat::setOpenGLCoreProfile(bool coreProfile) {
    this->coreProfile = coreProfile;
}
