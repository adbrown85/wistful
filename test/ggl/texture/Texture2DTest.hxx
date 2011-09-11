/*
 * Texture2DTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TEXTURE2DTEST_HXX
#define GGL_TEXTURE2DTEST_HXX
#include "ggl/common.h"
#include "ggl/texture/Texture2D.hpp"
#include "ggl/geometry/VertexBuffer.hpp"
#include "ggl/image/Image.hpp"
#include "ggl/image/BitmapReader.hpp"
#include "ggl/shader/ProgramBuilder.hpp"
#include "ggl/system/ErrorChecker.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowAdapter.hpp"
#include "ggl/window/WindowFactory.hpp"
namespace Ggl {


/**
 * @brief Unit test for Texture2D.
 */
class Texture2DTest {
public:
    void run();
};


/**
 * @brief Window listener for Texture2DTest.
 */
class Texture2DTestListener : public WindowAdapter {
public:
    void onWindowOpen(const WindowEvent &e);
    void onWindowPaint(const WindowEvent &e);
    void onWindowClose(const WindowEvent &e);
private:
    VertexBuffer *vbo;
    Texture *texture;
    GLuint program;
    GLuint vao;
// Helpers
    static GLuint createVAO(VertexBuffer *vb, GLuint program);
    static VertexBuffer* createVBO();
    static Image* createImage();
    static GLuint createProgram();
    static Texture* createTexture();
};

} /* namespace Ggl */
#endif
