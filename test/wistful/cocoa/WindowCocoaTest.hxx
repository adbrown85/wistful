/*
 * WindowCocoaTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_WINDOWCOCOATEST_HXX
#define WISTFUL_WINDOWCOCOATEST_HXX
#include "wistful/common.h"
#include "wistful/Window.hpp"
#include "wistful/WindowFactory.hpp"
namespace Wistful {


/**
 * Unit test for WindowCoca.
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


} /* namespace Wistful */
#endif
