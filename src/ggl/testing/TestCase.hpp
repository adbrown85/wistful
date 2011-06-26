/*
 * TestCase.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TESTCASE_HPP
#define GGL_TESTCASE_HPP
#include "ggl/common.h"
#include "ggl/testing/TestFixture.hpp"
namespace Ggl {


/**
 * @brief Part of a test that can be called.
 */
template <class T>
class TestCase {
public:
    TestCase(const std::string &name, void (T::*method)());
    void run(T &fixture);
private:
    std::string name;
    void (T::*method)();
};

/**
 * Creates a test case.
 * 
 * @param name Descriptive name
 * @param method Method to call on fixture
 */
template<class T>
inline
TestCase<T>::TestCase(const std::string &name,
                      void (T::*method)()) {
    this->name = name;
    this->method = method;
}

/**
 * Runs the test case on a fixture.
 * 
 * @param fixture Test fixture to run test case on
 */
template<class T>
inline
void TestCase<T>::run(T &fixture) {
    std::cout << "RUNNING " << name << std::endl;
    fixture.setUp();
    try {
        (fixture.*(method))();
    } catch (std::exception &e) {
        std::cout << "FAILED!" << std::endl;
        exit(1);
    }
    fixture.tearDown();
    std::cout << "PASSED" << std::endl;
}

}
#endif
