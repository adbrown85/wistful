/*
 * GlConfigTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GlConfig.hpp"

/** Test for GlConfig. */
class GlConfigTest {
public:
	void testGetInstances();
	void testGetInstancesMap();
};

/** Ensures all instances can be retrieved. */
void GlConfigTest::testGetInstances() {
	
	list<GlConfig> glcs = GlConfig::getInstances();
	list<GlConfig>::iterator it;
	
	cout << "Found " << glcs.size() << " GL configs." << endl;
}

/** Ensures instances can be retrieved using requirements. */
void GlConfigTest::testGetInstancesMap() {
	
	map<int,int> m;
	list<GlConfig> glcs;
	
	m[GLX_X_RENDERABLE] = 1;
	m[GLX_DRAWABLE_TYPE] = GLX_WINDOW_BIT;
	m[GLX_RENDER_TYPE] = GLX_RGBA_BIT;
	m[GLX_DOUBLEBUFFER] = 1;
	
	glcs = GlConfig::getInstances(m);
	
	cout << "Found " << glcs.size() << " GL configs." << endl;
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	GlConfigTest test;
	
	test.testGetInstances();
	test.testGetInstancesMap();
	return 0;
}
