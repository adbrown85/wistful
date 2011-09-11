/*
 * MeshBuilderTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MESHBUILDERTEST_HXX
#define GGL_MESHBUILDERTEST_HXX
#include "ggl/common.h"
#include "ggl/system/ErrorChecker.hpp"
#include "ggl/geometry/MeshBuilder.hpp"
#include "ggl/shader/ProgramBuilder.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
#include "ggl/window/WindowListener.hpp"
namespace Ggl {


/**
 * @brief Test for MeshBuilder.
 */
class MeshBuilderTest {
public:
    void run();
private:
// Nested classes
    class WindowObserver;
};


/**
 * @brief Window listener for the test.
 */
class MeshBuilderTest::WindowObserver : public WindowListener {
public:
    WindowObserver();
    virtual ~WindowObserver();
    virtual void onWindowOpen(const WindowEvent &we);
    virtual void onWindowPaint(const WindowEvent &we);
    virtual void onWindowKey(const WindowEvent &we);
    virtual void onWindowClose(const WindowEvent &we);
private:
    Mesh *mesh;
    GLuint program;
    GLuint vao;
// Helpers
    static Mesh* createMesh();
    static GLuint createProgram();
    static GLuint createVAO(Mesh *mesh, GLuint program);
};

} /* namespace Ggl */
#endif
