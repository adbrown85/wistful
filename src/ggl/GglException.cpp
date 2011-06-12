/*
 * GglException.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/GglException.hpp"

/**
 * Creates a GGL exception.
 * 
 * @param message Explanation shown to the user
 */
GglException::GglException(const string &message) throw() {
    this->message = message;
}

/**
 * Destroys the exception.
 */
GglException::~GglException() throw() {
    ;
}

/**
 * Returns the explanation that will be shown to the user.
 */
const char* GglException::what() const throw() {
    return message.c_str();
}
