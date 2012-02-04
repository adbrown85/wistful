/*
 * Exception.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_EXCEPTION_HPP
#define WISTFUL_EXCEPTION_HPP
#include "wistful/common.h"
namespace Wistful {


/**
 * @brief Exception thrown from within Wistful.
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
