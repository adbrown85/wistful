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
	list<GglConfig*> configs;
	list<GglConfig*>::iterator it;
	
	reqs[GLX_X_RENDERABLE] = 1;
	reqs[GLX_DRAWABLE_TYPE] = GLX_WINDOW_BIT;
	reqs[GLX_RENDER_TYPE] = GLX_RGBA_BIT;
	reqs[GLX_CONFIG_CAVEAT] = GLX_NONE;
	reqs[GLX_DOUBLEBUFFER] = 1;
	reqs[GLX_RED_SIZE] = 8;
	reqs[GLX_GREEN_SIZE] = 8;
	reqs[GLX_BLUE_SIZE] = 8;
	reqs[GLX_ALPHA_SIZE] = 8;
	configs = cf.create(reqs);
	
	cout << "Found " << configs.size() << " configurations." << endl;
	for (it=configs.begin(); it!=configs.end(); ++it) {
		cout << "----" << endl;
		cout << "  " << (*it)->getDepthSize() << endl;
		cout << "  " << (*it)->getStencilSize() << endl;
	}
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	GglConfigFactoryTest test;
	
	test.testCreate();
	return 0;
}
