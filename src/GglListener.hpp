/*
 * GglListener.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLLISTENER_HPP
#define GGLLISTENER_HPP
#include "ggl_common.h"
#include "GglEvent.hpp"


/* Forward declaration of window. */
class GglWindow;


/**
 * @brief Object that listens to GGL events.
 */
class GglListener {
public:
    GglListener();
    virtual ~GglListener();
    virtual void init(GglWindow &window) = 0;
    virtual void display(GglWindow &window) = 0;
    virtual void destroy(GglWindow &window) = 0;
    virtual void onKey(GglWindow &window, GglEvent &event) = 0;
};

#endif
