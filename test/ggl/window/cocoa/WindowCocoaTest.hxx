/*
 * WindowCocoaTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_WINDOWCOCOATEST_HXX
#define GGL_WINDOWCOCOATEST_HXX
#include "ggl/common.h"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
namespace Ggl {


/**
 * @brief Unit test for GglWindowCoca.
 */
class WindowCocoaTest {
public:
    void run();
};


class FakeWindowListener : public WindowListener {
public:
    void onWindowOpen(const WindowEvent &e);
    void onWindowPaint(const WindowEvent &e);
    void onWindowKey(const WindowEvent &e);
    void onWindowClose(const WindowEvent &e);
};


} /* namespace Ggl */
#endif
