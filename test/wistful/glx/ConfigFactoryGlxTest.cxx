/*
 * ConfigFactoryGlxTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "config.h"
#include "wistful/glx/ConfigFactoryGlx.hpp"
using namespace std;
namespace Wistful {

/**
 * Test for ConfigFactoryGlx.
 */
class ConfigFactoryGlxTest {
public:
    void testCreate();
};

/** Ensures configurations can be created correctly. */
void ConfigFactoryGlxTest::testCreate() {

    ConfigFactoryGlx cf;
    map<int,int> reqs;
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

} // namespace Wistful

/** Runs the test. */
int main(int argc, char *argv[]) {

    Wistful::ConfigFactoryGlxTest test;

    test.testCreate();
    return 0;
}
