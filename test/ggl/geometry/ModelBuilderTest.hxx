/*
 * ModelBuilderTest.hxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MODELBUILDERTEST_HXX
#define GGL_MODELBUILDERTEST_HXX
#include "ggl/common.h"
#include "ggl/geometry/MeshBuilder.hpp"
#include "ggl/geometry/Model.hpp"
#include "ggl/geometry/ModelBuilder.hpp"
#include "ggl/shader/ProgramBuilder.hpp"
#include "ggl/window/Window.hpp"
#include "ggl/window/WindowFactory.hpp"
#include "ggl/window/WindowAdapter.hpp"
namespace Ggl {


/**
 * @brief Test for %ModelBuilder.
 */
class ModelBuilderTest {
public:
    void run();
private:
    class WindowObserver;
};


/**
 * @brief Observer of window events.
 */
class ModelBuilderTest::WindowObserver : public WindowAdapter {
public:
    WindowObserver();
    virtual ~WindowObserver();
    virtual void onWindowOpen(const WindowEvent &e);
    virtual void onWindowPaint(const WindowEvent &e);
    virtual void onWindowClose(const WindowEvent &e);
private:
    Mesh *mesh;
    GLuint program;
    Model *model;
// Helpers
    static GLuint createProgram();
    static Mesh* createMesh();
    static Model* createModel(Mesh *mesh, GLuint program);
};


} /* namespace Ggl */
#endif
