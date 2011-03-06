/*
 * GlConfigFactoryTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */


/** Test for GlConfigFactory. */
class GlConfigFactoryTest {
public:
	void testCreate();
};


/** Ensures configurations can be created correctly. */
void GlConfigFactoryTest::testCreate() {
	
	GlConfigFactory glcf;
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	GlConfigFactoryTest test;
	
	test.testCreate();
	return 0;
}
