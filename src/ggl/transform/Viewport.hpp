/*
 * Viewport.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_VIEWPORT_HPP
#define GGL_VIEWPORT_HPP
#include "ggl/common.h"
#include "ggl/Exception.hpp"
#include "ggl/transform/ViewportListener.hpp"
namespace Ggl {


/**
 * Area of a window being rendered to.
 * 
 * @ingroup transform
 */
class Viewport {
public:
    Viewport();
    Viewport(int x, int y, int width, int height);
    virtual ~Viewport();
    virtual void addViewportListener(ViewportListener *listener);
    virtual void removeViewportListener(ViewportListener *listener);
    virtual void toArray(int arr[4]) const;
// Accessors and mutators
    virtual int getX() const;
    virtual int getY() const;
    virtual void setLocation(int x, int y);
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual void setSize(int width, int height);
protected:
    void fireViewportEvent();
private:
    int x;                                   // Left side of window area
    int y;                                   // Bottom of window area
    int width;                               // Size of window area on X axis
    int height;                              // Size of window area on Y axis
    std::list<ViewportListener*> listeners;  // Observers of viewport
// Constants
    static const int DEFAULT_X = 0;
    static const int DEFAULT_Y = 0;
    static const int DEFAULT_WIDTH = 0;
    static const int DEFAULT_HEIGHT = 0;
};

} /* namespace Ggl */
#endif
