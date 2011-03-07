/*
 * GglWindowGlxTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindow.hpp"
#include <iostream>
using namespace std;


/** Test for GlWindowGlx. */
class GlWindowGlxTest {
public:
	void testShow();
};

/** Ensures window can be shown. */
void GlWindowGlxTest::testShow() {
	
	GlWindowGlx window;
	
	window.show();
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	GlWindowGlxTest test;
	
	test.testShow();
}
