/*
 * Texture2DTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TEXTURE2DTEST_HXX
#define GGL_TEXTURE2DTEST_HXX
#define GGL_TEST_FIXTURE Texture2DTest
#include "ggl/common.h"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
#include "ggl/texture/Texture2D.hpp"
#include "ggl/geometry/VertexBuffer.hpp"
#include "ggl/geometry/VertexBufferBuilder.hpp"
#include "ggl/shader/ProgramBuilder.hpp"
#include "ggl/shader/ShaderBuilder.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowAdapter.hpp"
#include "ggl/window/WindowFactory.hpp"
namespace Ggl {


/**
 * @brief Unit test for Texture2D.
 */
class Texture2DTest : public TestFixture {
public:
    void test();
};


/**
 * @brief Window listener for Texture2DTest.
 */
class Texture2DTestListener : public WindowAdapter {
public:
    void onWindowOpen(const WindowEvent &e);
    void onWindowPaint(const WindowEvent &e);
private:
    VertexBuffer *vbo;
    GLuint program;
    GLuint vao;
// Helpers
    static GLuint createVAO(VertexBuffer *vb, GLuint program);
    static VertexBuffer* createVBO();
    static GLuint createProgram();
    static GLuint loadShader(const std::string &filename);
};

} /* namespace Ggl */
#endif
