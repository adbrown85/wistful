/*
 * GglException.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLEXCEPTION_HPP
#define GGLEXCEPTION_HPP
#include "ggl/common.h"


/**
 * @brief Exception thrown from within GGL.
 */
class GglException : public std::exception {
public:
    GglException(const std::string &message) throw();
    virtual ~GglException() throw();
    virtual const char* what() const throw();
private:
    std::string message;
};

#endif