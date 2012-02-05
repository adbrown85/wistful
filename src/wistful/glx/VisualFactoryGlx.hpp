/*
 * VisualFactoryGlx.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_VISUALFACTORYGLX_HPP
#define WISTFUL_VISUALFACTORYGLX_HPP
#include <list>
#include "wistful/common.h"
#include "wistful/WindowException.hpp"
#include "wistful/WindowFormat.hpp"
namespace Wistful {


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

} // namespace Wistful
#endif // WISTFUL_VISUALFACTORYGLX_HPP
