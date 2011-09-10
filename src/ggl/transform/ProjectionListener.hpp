/*
 * ProjectionListener.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PROJECTIONLISTENER_HPP
#define GGL_PROJECTIONLISTENER_HPP
namespace Ggl {


// Forward declaration of Projection
class Projection;

/**
 * Observer of projection events.
 * 
 * @ingroup transform
 */
class ProjectionListener {
public:
    ProjectionListener();
    virtual ~ProjectionListener();
    virtual void onProjectionEvent(Projection *projection) = 0;
};

} /* namespace Ggl */
#endif
