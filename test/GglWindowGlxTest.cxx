/*
 * GglWindowGlxTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowGlx.hpp"
#include "GglConfigFactory.hpp"
#include <iostream>
using namespace std;


/** Test for GlWindowGlx. */
class GglWindowGlxTest {
public:
	void testShow();
};

/** Ensures window can be shown. */
void GglWindowGlxTest::testShow() {
	
	GglConfigFactory cf;
	GglWindowGlx *window;
	map<int,int> m;
	list<GglConfig*> configs;
	GglConfig* config;
	
	m[GLX_RENDER_TYPE] = GLX_RGBA_BIT;
	m[GLX_X_RENDERABLE] = True;
	m[GLX_DRAWABLE_TYPE] = GLX_WINDOW_BIT;
	m[GLX_DOUBLEBUFFER] = True;
	m[GLX_RED_SIZE] = 8;
	m[GLX_GREEN_SIZE] = 8;
	m[GLX_BLUE_SIZE] = 8;
	configs = cf.create(m);
	config = *(configs.begin());
	
	window = new GglWindowGlx((GglConfigGlx*) config);
	window->open();
	sleep(4);
	window->close();
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	GglWindowGlxTest test;
	
	test.testShow();
}
