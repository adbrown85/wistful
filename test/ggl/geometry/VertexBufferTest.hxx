/*
 * VertexBufferTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_VERTEXBUFFERTEST_HXX
#define GGL_VERTEXBUFFERTEST_HXX
#include "ggl/common.h"
#include "ggl/geometry/VertexBuffer.hpp"
#include "ggl/shader/ProgramBuilder.hpp"
#include "ggl/system/ErrorChecker.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
namespace Ggl {


/**
 * @brief Unit test for VertexBuffer.
 */
class VertexBufferTest {
public:
    void run();
};


/**
 * @brief Window listener for VertexBufferTest.
 */
class VertexBufferTestListener : public WindowListener {
public:
    VertexBufferTestListener();
    virtual void onWindowOpen(const WindowEvent&);
    virtual void onWindowPaint(const WindowEvent&);
    virtual void onWindowKey(const WindowEvent &event);
    virtual void onWindowClose(const WindowEvent&);
private:
    VertexBuffer *vbo;
    GLuint program;
    GLint pointLoc;
    GLuint vao;
// Helpers
    static GLuint createProgram();
};

}
#endif
