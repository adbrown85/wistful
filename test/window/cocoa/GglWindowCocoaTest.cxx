/*
 * GglWindowCocoaTest.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GglWindowCocoa.hpp"
#include "GglFactory.hpp"
using namespace std;

/**
 * Test for GglWindowCoca.
 */
class GglWindowCocoaTest {
public:
    void testOpen();
};

/**
 * Ensures window can be opened.
 */
void GglWindowCocoaTest::testOpen() {
    
    GglWindowFactory *factory = GglFactory::getWindowFactory();
    GglWindow *window = factory->create();
    
    GglWindow::open(window);
}

/*
 * Runs the program.
 */
int main(int argc, char *argv[]) {
    
    GglWindowCocoaTest test;
    
    test.testOpen();
}
