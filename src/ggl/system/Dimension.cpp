/*
 * Dimension.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/system/Dimension.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates an empty dimension.
 */
Dimension::Dimension() {
    this->width = 0;
    this->height = 0;
    this->depth = 0;
}

/**
 * Creates a dimension from individual sizes.
 * 
 * @param width Size of dimension on X axis
 * @param height Size of dimension on Y axis
 * @param depth Size of dimension on Z axis
 */
Dimension::Dimension(size_t width, size_t height, size_t depth) {
    this->width = width;
    this->height = height;
    this->depth = depth;
}

/**
 * Destroys the dimension.
 */
Dimension::~Dimension() {
    ;
}

//----------------------------------------
// Getters and setters
//

/**
 * Returns size of dimension on the Z axis.
 */
size_t Dimension::getDepth() const {
    return depth;
}

/**
 * Changes the size of the dimension on the Z axis.
 * 
 * @param depth Size on Z axis
 */ 
void Dimension::setDepth(size_t depth) {
    this->depth = depth;
}

/**
 * Returns size of dimension on the Y axis.
 */
size_t Dimension::getHeight() const {
    return height;
}

/**
 * Changes the size of the dimension on the Y axis.
 * 
 * @param height Size on Y axis
 */
void Dimension::setHeight(size_t height) {
    this->height = height;
}

/**
 * Returns size of dimension on the X axis. 
 */
size_t Dimension::getWidth() const {
    return width;
}

/**
 * Changes the size of the dimension on the X axis.
 * 
 * @param width Size on X axis
 */
void Dimension::setWidth(size_t width) {
    this->width = width;
}

