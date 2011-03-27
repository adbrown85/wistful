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
	
	GglWindow *window = new GglWindowGlx();
	
	window->open();
	sleep(4);
	window->close();
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	GglWindowGlxTest test;
	
	test.testShow();
}
