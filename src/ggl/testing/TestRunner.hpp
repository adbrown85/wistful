/*
 * TestRunner.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TESTRUNNER_HPP
#define GGL_TESTRUNNER_HPP
#include "ggl/common.h"
#include "ggl/testing/TestFixture.hpp"
#include "ggl/testing/TestCase.hpp"
#include "ggl/testing/TestSuite.hpp"
namespace Ggl {

/* Macro for making a test runner */
#define GGL_TEST_SUITE \
int main(int argc, char *argv[]) { \
    TestSuite<GGL_TEST_FIXTURE> testSuite; \
    TestRunner<GGL_TEST_FIXTURE> testRunner;

/* Macro for adding a test case */
#define GGL_ADD_TEST(X) \
    testSuite.addTestCase(#X, &GGL_TEST_FIXTURE::X);

/* Macro for running the fixture */
#define GGL_RUN_TESTS \
    testRunner.runTestSuite(testSuite); \
    return 0; \
}


/**
 * @brief Utility for running tests.
 */
template <typename T>
class TestRunner {
public:
    TestRunner() {}
    virtual ~TestRunner() {}
    void runTestSuite(TestSuite<T> &testSuite);
};

/**
 * Runs each test case on a fixture.
 * 
 * @param testFixture
 */
template <typename T>
inline
void TestRunner<T>::runTestSuite(TestSuite<T> &testSuite) {
    
    T testFixture;
    typename TestSuite<T>::iterator it;
    
    for (it=testSuite.begin(); it!=testSuite.end(); ++it) {
        it->run(testFixture);
    }
}


} // namespace Ggl
#endif
