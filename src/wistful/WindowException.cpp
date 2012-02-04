/*
 * WindowException.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "wistful/WindowException.hpp"
using namespace Wistful;
using namespace std;

/**
 * Creates a window exception.
 *
 * @param message Explanation shown to the user
 */
WindowException::WindowException(const string &message) throw() {
    this->message = message;
}

/**
 * Destroys the window exception.
 */
WindowException::~WindowException() throw() {
    ;
}

/**
 * Returns the explanation that will be shown to the user.
 */
const char* WindowException::what() const throw() {
    return message.c_str();
}
