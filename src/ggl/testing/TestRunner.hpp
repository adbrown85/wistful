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
namespace Ggl {


/**
 * @brief Utility for running tests.
 */
template <typename T>
class TestRunner {
public:
    TestRunner() {}
    virtual ~TestRunner() {}
    void add(const std::string &name, void (T::*method)());
    void add(TestCase<T> testCase);
    void run(T &testFixture);
private:
    std::list<TestCase<T> > testCases;
};

/**
 * Adds a test case to the test runner.
 * 
 * @param name Name of the test case
 * @param method Address to the method to call
 */
template <typename T>
inline
void TestRunner<T>::add(const std::string &name,
                        void (T::*method)()) {
    add(TestCase<T>(name, method));
}

/**
 * Adds a test case to the test runner.
 * 
 * @param name Name of the test case
 * @param method Address to the method to call
 */
template <typename T>
inline
void TestRunner<T>::add(TestCase<T> tc) {
    testCases.push_back(tc);
}

/**
 * Runs each test case on a fixture.
 * 
 * @param testFixture
 */
template <typename T>
inline
void TestRunner<T>::run(T &testFixture) {
    
    typename std::list<TestCase<T> >::iterator it;
    
    for (it=testCases.begin(); it!=testCases.end(); ++it) {
        testFixture.setUp();
        it->run(testFixture);
        testFixture.tearDown();
    }
}


} // namespace Ggl
#endif
