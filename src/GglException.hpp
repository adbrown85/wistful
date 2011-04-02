/*
 * GglException.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLEXCEPTION_HPP
#define GGLEXCEPTION_HPP
#include "common.h"


/**
 * @brief Exception thrown from within GGL.
 */
class GglException : public exception {
public:
    GglException(const string &message) throw();
    virtual ~GglException() throw();
    virtual const char* what() const throw();
private:
    string message;
};

#endif
