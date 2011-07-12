/*
 * ShaderLoaderTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_SHADERBUILDERTEST_HXX
#define GGL_SHADERBUILDERTEST_HXX
#define GGL_TEST_FIXTURE ShaderLoaderTest
#include "ggl/common.h"
#include "ggl/shader/ShaderLoader.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
namespace Ggl {


/**
 * @brief Unit test for ShaderLoader.
 */
class ShaderLoaderTest : public TestFixture {
public:
    void testLoad();
};


/**
 * @brief Window listener for ShaderLoaderTest.
 */
class ShaderLoaderTestListener : public WindowListener {
public:
    virtual void onWindowOpen(const WindowEvent &e);
    virtual void onWindowPaint(const WindowEvent &e);
    virtual void onWindowKey(const WindowEvent &e);
    virtual void onWindowClose(const WindowEvent &e);
};

} /* namespace Ggl */
#endif
