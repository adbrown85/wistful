/*
 * Matrix.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <ctime>
#include "ggl/common.h"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
#include "ggl/math/Matrix.hpp"
using namespace std;
using namespace Ggl;


/**
 * @brief Unit test for Matrix.
 */
class MatrixTest : public TestFixture {
public:
	void setUp();
	void testInverse();
	void testMultiplyTime();
	void testSetArray();
	void testTranspose();
	void testMultiplyVector();
private:
	Matrix m1, m2, m3;
};

void MatrixTest::setUp() {
    
    float arr[4][4] = { {4.0, 4.0, 8.0, 7.0},
                        {3.0, 2.0, 4.0, 6.0},
                        {1.0, 6.0, 4.0, 5.0},
                        {1.0, 2.0, 3.0, 4.0} };
    
	m1 = Matrix(arr);
	m2 = Matrix(1.0);
	m3 = Matrix(1.0);
}

void MatrixTest::testInverse() {
	
	m2 = inverse(m1);
	m3 = m1 * m2;
	
	for (int i=0; i<4; ++i) {
		assertEquals(m3(i,i), 1.0);
	}
	
	for (int i=0; i<3; ++i) {
		for (int j=i+1; j<4; ++j) {
			assertEquals(m3(i,j), 0.0);
		}
	}
	
	for (int i=1; i<4; ++i) {
		for (int j=0; j<i; ++j) {
			assertEquals(m3(i,j), 0.0);
		}
	}
}

void MatrixTest::testSetArray() {
	
	float arr[16] = { 1.0,  2.0,  3.0,  4.0,
	                  5.0,  6.0,  7.0,  8.0,
	                  9.0, 10.0, 11.0, 12.0,
	                 13.0, 14.0, 15.0, 16.0};
	
	m2 = Matrix(arr);
	
	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			assertEquals(arr[i*4+j], m2(j,i));
		}
	}
}

void MatrixTest::testTranspose() {
    
    float arr[4][4] = { {4.0, 3.0, 1.0, 1.0},
                        {4.0, 2.0, 6.0, 2.0},
                        {8.0, 4.0, 4.0, 3.0},
                        {7.0, 6.0, 5.0, 4.0}};
    
    m2 = Matrix(arr);
	m3 = transpose(m1);
	
	for (int i=0; i<4; ++i) {
	    for (int j=0; j<4; ++j) {
	        assertEquals(m2(i,j), m3(i,j));
	    }
	}
}

void MatrixTest::testMultiplyVector() {
	
	Vec4 u(8.0, 3.0, 1.0, 7.0);
	Vec4 v = m1 * u;
	
	assertEquals(101, v.x);
	assertEquals( 76, v.y);
	assertEquals( 65, v.z);
	assertEquals( 45, v.w);
}

#define GGL_TEST_FIXTURE MatrixTest
GGL_TEST_SUITE
GGL_ADD_TEST(testInverse)
GGL_ADD_TEST(testSetArray)
GGL_ADD_TEST(testTranspose)
GGL_ADD_TEST(testMultiplyVector)
GGL_RUN_TESTS

