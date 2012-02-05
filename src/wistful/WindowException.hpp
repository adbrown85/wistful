/*
 * WindowException.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_WINDOWEXCEPTION_HPP
#define WISTFUL_WINDOWEXCEPTION_HPP
#include "wistful/common.h"
#include <string>
namespace Wistful {


/**
 * @brief Exception thrown from within Wistful.
 */
class WindowException : public std::exception {
public:
    WindowException(const std::string &message) throw();
    virtual ~WindowException() throw();
    virtual const char* what() const throw();
private:
    std::string message;
};

}
#endif
