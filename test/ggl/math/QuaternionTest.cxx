/*
 * QuaternionTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/common.h"
#include "ggl/math/Quaternion.hpp"
#include "ggl/testing/TestRunner.hpp"
using namespace std;
using namespace Ggl;

/**
 * @brief Unit test for Quaternion.
 */
class QuaternionTest : public TestFixture {
public:
	void testToMat4();
	void testMultiply();
private:
	Mat4 mat;
	Quaternion quaA, quaB, quaC;
};

void QuaternionTest::testToMat4() {
	quaA.set(45, Vec4(0,1,0));
	print(quaA);
	mat = quaA.toMat4();
	print(mat);
}

void QuaternionTest::testMultiply() {
	quaA.set(45, Vec4(0,1,0));
	quaB.set(30, Vec4(0,1,0));
	quaC = quaA * quaB;
	mat = quaC.toMat4();
	print(mat);
}

/*
 * Runs the test.
 */
#define GGL_TEST_FIXTURE QuaternionTest
GGL_TEST_SUITE
GGL_ADD_TEST(testToMat4)
GGL_ADD_TEST(testMultiply)
GGL_RUN_TESTS

