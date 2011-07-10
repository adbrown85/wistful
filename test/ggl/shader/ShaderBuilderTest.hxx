/*
 * ShaderBuilderTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_SHADERBUILDERTEST_HXX
#define GGL_SHADERBUILDERTEST_HXX
#define GGL_TEST_FIXTURE ShaderBuilderTest
#include "ggl/common.h"
#include "ggl/shader/ShaderBuilder.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
namespace Ggl {


/**
 * @brief Unit test for ShaderBuilder.
 */
class ShaderBuilderTest : public TestFixture {
public:
    void testBuild();
};


/**
 * @brief Window listener for ShaderBuilderTest.
 */
class ShaderBuilderTestListener : public WindowListener {
public:
    virtual void onWindowOpen(const WindowEvent &e);
    virtual void onWindowPaint(const WindowEvent &e);
    virtual void onWindowKey(const WindowEvent &e);
    virtual void onWindowClose(const WindowEvent &e);
};

} /* namespace Ggl */
#endif
