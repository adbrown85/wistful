/*
 * Vec4Test.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/common.h"
#include "ggl/math/Vec4.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
using namespace std;
using namespace Ggl;


/**
 * @brief Unit test for Vec4.
 */
class Vec4Test : public TestFixture {
public:
    void setUp();
	void testAdd();
	void testSubtract();
	void testMultiply();
	void testDivide();
private:
	Vec4 A, B, C;
};

void Vec4Test::setUp() {
	A.set(2, 2, 2);
	B.set(2, 4, 5);
}

void Vec4Test::testAdd() {
	
	C = A + B;
	assertEquals(C.x, 4);
	assertEquals(C.y, 6);
	assertEquals(C.z, 7);
}

void Vec4Test::testSubtract() {
	
	C = A - B;
	assertEquals(C.x, 0);
	assertEquals(C.y, -2);
	assertEquals(C.z, -3);
}

void Vec4Test::testMultiply() {
	
	C = A * B;
	assertEquals(C.x, 4);
	assertEquals(C.y, 8);
	assertEquals(C.z, 10);
}

void Vec4Test::testDivide() {
	
	C = A / B;
	assertEquals(C.x, 1.0);
	assertEquals(C.y, 0.5);
	assertEquals(C.z, 0.4);
}


/*
 * Runs the test.
 */
int main(int argc, char *argv[]) {
    
    Vec4Test fixture;
    TestRunner<Vec4Test> runner;
    
    runner.add("testAdd", &Vec4Test::testAdd);
    runner.add("testSubtract", &Vec4Test::testSubtract);
    runner.add("testMultiply", &Vec4Test::testMultiply);
    runner.add("testDivide", &Vec4Test::testDivide);
    
    runner.run(fixture);
    return 0;
}


