/*
 * VisualFactoryGlx.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_VISUALFACTORYGLX_HPP
#define GGL_VISUALFACTORYGLX_HPP
#include "ggl/common.h"
#include "ggl/Exception.hpp"
#include "ggl/window/WindowFormat.hpp"
namespace Ggl {


class VisualFactoryGlx {
public:
    VisualFactoryGlx();
    virtual ~VisualFactoryGlx();
    XVisualInfo* createVisualInfo(const WindowFormat &wf);
private:
    Display *display;
// Helpers
    static Display* createDisplay() throw(std::exception);
    static int* toArray(const WindowFormat &wf);
    static std::list<int> toList(const WindowFormat &wf);
};

} // namespace Ggl
#endif // GGL_VISUALFACTORYGLX_HPP
