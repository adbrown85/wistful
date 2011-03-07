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
class GglWindowGlxTest {
public:
	void testShow();
};

/** Ensures window can be shown. */
void GglWindowGlxTest::testShow() {
	
	GglWindowGlx window;
	
	window.show();
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	GglWindowGlxTest test;
	
	test.testShow();
}
