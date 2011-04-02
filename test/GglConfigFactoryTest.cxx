/*
 * GglConfigFactoryTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglConfigFactory.hpp"


/** Test for GglConfigFactory. */
class GglConfigFactoryTest {
public:
    void testCreate();
};

/** Ensures configurations can be created correctly. */
void GglConfigFactoryTest::testCreate() {
    
    GglConfigFactory cf;
    map<int,int> reqs;
    GglConfig *config;
    
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
    
    cout << "  " << ((GglConfigGlx*) config)->getId() << endl;
    cout << "  " << config->getDepthSize() << endl;
    cout << "  " << config->getStencilSize() << endl;
}

/** Runs the test. */
int main(int argc, char *argv[]) {
    
    GglConfigFactoryTest test;
    
    test.testCreate();
    return 0;
}
