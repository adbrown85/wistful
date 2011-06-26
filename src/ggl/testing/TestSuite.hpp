/*
 * TestSuite.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TESTSUITE_HPP
#define GGL_TESTSUITE_HPP
#include "ggl/common.h"
#include "ggl/testing/TestCase.hpp"
namespace Ggl {


/**
 * Collection of test cases to run.
 */
template <typename T>
class TestSuite {
public:
    typedef typename std::list<TestCase<T> >::iterator iterator;
public:
    TestSuite() {}
    virtual ~TestSuite() {}
    void addTestCase(const std::string &name, void (T::*method)());
    void addTestCase(TestCase<T> testCase);
    iterator begin();
    iterator end();
    std::list<TestCase<T> > getTestCases();
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
void TestSuite<T>::addTestCase(const std::string &name,
                               void (T::*method)()) {
    addTestCase(TestCase<T>(name, method));
}

/**
 * Adds a test case to the test runner.
 * 
 * @param name Name of the test case
 * @param method Address to the method to call
 */
template <typename T>
inline
void TestSuite<T>::addTestCase(TestCase<T> testCase) {
    testCases.push_back(testCase);
}

template <typename T>
inline
std::list<TestCase<T> > TestSuite<T>::getTestCases() {
    return testCases;
}

template <typename T>
inline
typename TestSuite<T>::iterator
TestSuite<T>::begin() {
    return testCases.begin();
}

template <typename T>
inline
typename TestSuite<T>::iterator
TestSuite<T>::end() {
    return testCases.end();
}

} // namespace Ggl
#endif
