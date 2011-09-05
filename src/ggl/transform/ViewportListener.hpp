/*
 * ViewportListener.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_VIEWPORTLISTENER_HPP
#define GGL_VIEWPORTLISTENER_HPP
#include "ggl/common.h"
namespace Ggl {


/* Forward declarations */
class Viewport;

/**
 * @brief Observer of viewport events.
 */
class ViewportListener {
public:
    ViewportListener();
    virtual ~ViewportListener();
    virtual void onViewportEvent(Viewport *viewport) = 0;
};

} /* namespace Ggl */
#endif
