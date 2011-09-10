/*
 * Dimension.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_DIMENSION_HPP
#define GGL_DIMENSION_HPP
#include "ggl/common.h"
namespace Ggl {


/**
 * Width, height, and depth of an item.
 *
 * @ingroup system
 */
class Dimension {
public:
    Dimension();
    Dimension(size_t width, size_t height, size_t depth);
    virtual ~Dimension();
// Getters and setters
    size_t getDepth() const;
    void setDepth(size_t depth);
    size_t getHeight() const;
    void setHeight(size_t height);
    size_t getWidth() const;
    void setWidth(size_t width);
private:
    size_t width;            // Size on X axis
    size_t height;           // Size on Y axis
    size_t depth;            // Size on Z axis
};

} /* namespace Ggl */
#endif
