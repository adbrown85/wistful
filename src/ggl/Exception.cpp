/*
 * Exception.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/Exception.hpp"

/**
 * Creates a GGL exception.
 * 
 * @param message Explanation shown to the user
 */
Ggl::Exception::Exception(const std::string &message) throw() {
    this->message = message;
}

/**
 * Destroys the exception.
 */
Ggl::Exception::~Exception() throw() {
    ;
}

/**
 * Returns the explanation that will be shown to the user.
 */
const char* Ggl::Exception::what() const throw() {
    return message.c_str();
}
