/*
 * GglWindowFormat.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowFormat.hpp"

/**
 * Creates a default window format.
 */
GglWindowFormat::GglWindowFormat() {
    colorSize = DEFAULT_COLOR_SIZE;
    depthSize = DEFAULT_DEPTH_SIZE;
    majorVersion = DEFAULT_MAJOR_VERSION;
    minorVersion = DEFAULT_MINOR_VERSION;
}

/**
 * Destroys the window format.
 */
GglWindowFormat::~GglWindowFormat() {
    ;
}

/**
 * Returns number of bits used for a pixel in the color buffer.
 */
int
GglWindowFormat::getColorSize() const {
    return colorSize;
}

/**
 * Changes the number of bits used for a pixel in the color buffer.
 * 
 * @param colorSize Size of color buffer pixel in bits
 * @throw GglException if size is negative
 */
void
GglWindowFormat::setColorSize(int colorSize) {
    if (colorSize < 0) {
        throw GglException("Color size is negative!");
    } else {
        this->colorSize = colorSize;
    }
}

/**
 * Returns number of bits used for a pixel in the depth buffer.
 */
int
GglWindowFormat::getDepthSize() const {
    return depthSize;
}

/**
 * Changes the number of bits used for a pixel in the depth buffer. 
 * 
 * @param depthSize Size of depth buffer pixel in bits
 * @throw GglException if size is negative
 */
void
GglWindowFormat::setDepthSize(int depthSize) {
    if (depthSize < 0) {
        throw GglException("Depth size is negative!");
    } else {
        this->depthSize = depthSize;
    }
}

/**
 * Returns major version number of OpenGL.
 */
int
GglWindowFormat::getOpenGLMajorVersion() const {
    return majorVersion;
}

/**
 * Returns minor version number of OpenGL.
 */
int
GglWindowFormat::getOpenGLMinorVersion() const {
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
GglWindowFormat::setOpenGLVersion(int major,
                                  int minor) {
    if (major < 1) {
        throw GglException("Major version less than 1!");
    } else if (minor < 0) {
        throw GglException("Minor version less than 0!");
    } else {
        this->majorVersion = major;
        this->minorVersion = minor;
    }
}

/**
 * Returns OpenGL profile for the window.
 */
GglOpenGLProfile
GglWindowFormat::getOpenGLProfile() const {
    return profile;
}

/**
 * Changes the OpenGL profile.
 * 
 * @param profile Either GGL_CORE_PROFILE or GGL_COMPATIBILITY_PROFILE
 */
void
GglWindowFormat::setOpenGLProfile(GglOpenGLProfile profile) {
    this->profile = profile;
}
