/*
 * PreprocessorTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/common.h"
#include "ggl/shader/Preprocessor.hpp"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestRunner.hpp"
using namespace std;
using namespace Ggl;

/**
 * Unit test for Preprocessor.
 */
class PreprocessorTest : public TestFixture {
public:
	void testParse();
};

/**
 * Ensures a file can be parsed correctly.
 */
void PreprocessorTest::testParse() {
	
	Preprocessor pp;
	Code code;
	Code::iterator it;
	int i;
	string filename = "test/ggl/shader/PreprocessorTest.glsl";
	int numbers[6] = {1, 4, 7, 11, 13, 14};
	string lines[6] = {"#version 130\n",
	                   "uniform vec4 Color = vec4(1.0);\n",
	                   "out vec4 FragColor;\n",
	                   "void main() {\n",
	                   "    FragColor = Color;\n",
	                   "}\n"};
	
	pp.parse(filename);
	code = pp.getCode();
	for (it=code.begin(); it!=code.end(); ++it) {
		i = distance(code.begin(), it);
		cout << it->text;
		assert(it->filename == filename);
		assert(it->number == numbers[i]);
		assert(it->text == lines[i]);
	}
}

/**
 * Runs the tests.
 */
#define GGL_TEST_FIXTURE PreprocessorTest
GGL_TEST_SUITE
GGL_ADD_TEST(testParse)
GGL_RUN_TESTS

