/*
 * ProgramBuilderTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_PROGRAMBUILDERTEST_HXX
#define GGL_PROGRAMBUILDERTEST_HXX
#include "ggl/common.h"
#include "ggl/shader/ProgramBuilder.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
namespace Ggl {


/**
 * Unit test for ProgramBuilder.
 */
class ProgramBuilderTest {
public:
    void run();
};


/**
 * Window listener for ProgramBuilderTest.
 */
class ProgramBuilderTestListener : public WindowListener {
    virtual void onWindowOpen(const WindowEvent &e);
    virtual void onWindowPaint(const WindowEvent &e);
    virtual void onWindowKey(const WindowEvent &e);
    virtual void onWindowClose(const WindowEvent &e);
};

} /* namespace Ggl */
#endif
