/*
 * GglConfigFactoryTest.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */


/** Test for GglConfigFactory. */
class GglConfigFactoryTest {
public:
	void testCreate();
};


/** Ensures configurations can be created correctly. */
void GglConfigFactoryTest::testCreate() {
	
	GglConfigFactory cf;
}

/** Runs the test. */
int main(int argc, char *argv[]) {
	
	GglConfigFactoryTest test;
	
	test.testCreate();
	return 0;
}
