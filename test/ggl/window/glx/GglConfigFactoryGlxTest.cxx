/*
 * GglConfigFactoryGlxTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/window/glx/GglConfigFactoryGlx.hpp"
namespace Ggl {

/** Test for GglConfigFactoryGlx. */
class ConfigFactoryGlxTest {
public:
    void testCreate();
};

/** Ensures configurations can be created correctly. */
void ConfigFactoryGlxTest::testCreate() {
    
    ConfigFactoryGlx cf;
    std::map<int,int> reqs;
    GLXFBConfig config;
    
    reqs[GLX_X_RENDERABLE] = 1;
    reqs[GLX_DRAWABLE_TYPE] = GLX_WINDOW_BIT;
    reqs[GLX_RENDER_TYPE] = GLX_RGBA_BIT;
    reqs[GLX_CONFIG_CAVEAT] = GLX_NONE;
    reqs[GLX_DOUBLEBUFFER] = 1;
    reqs[GLX_RED_SIZE] = 8;
    reqs[GLX_GREEN_SIZE] = 8;
    reqs[GLX_BLUE_SIZE] = 8;
    reqs[GLX_ALPHA_SIZE] = 8;
    config = cf.create(reqs);
}

} // namespace Ggl

/** Runs the test. */
int main(int argc, char *argv[]) {
    
    Ggl::ConfigFactoryGlxTest test;
    
    test.testCreate();
    return 0;
}
