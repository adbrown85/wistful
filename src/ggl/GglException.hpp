/*
 * GglException.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGLEXCEPTION_HPP
#define GGLEXCEPTION_HPP
#include "ggl/common.h"
namespace Ggl {


/**
 * @brief Exception thrown from within GGL.
 */
class Exception : public std::exception {
public:
    Exception(const std::string &message) throw();
    virtual ~Exception() throw();
    virtual const char* what() const throw();
private:
    std::string message;
};

}
#endif
