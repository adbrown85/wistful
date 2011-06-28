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
	void testRotate();
private:
	Mat4 mat;
	Quaternion q;
};

void QuaternionTest::testToMat4() {
	q = Quaternion(45, Vec4(0,1,0));
	print(q);
	mat = q.toMat4();
	print(mat);
}

void QuaternionTest::testRotate() {
	q = Quaternion(30, Vec4(0,1,0));
	q.rotate(45, Vec4(0,1,0));
	mat = q.toMat4();
	print(mat);
}

/*
 * Runs the test.
 */
#define GGL_TEST_FIXTURE QuaternionTest
GGL_TEST_SUITE
GGL_ADD_TEST(testToMat4)
GGL_ADD_TEST(testRotate)
GGL_RUN_TESTS

