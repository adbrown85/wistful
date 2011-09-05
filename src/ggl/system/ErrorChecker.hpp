/*
 * ErrorChecker.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_ERRORCHECKER_HPP
#define GGL_ERRORCHECKER_HPP
#include "ggl/common.h"
#include "ggl/Exception.hpp"
namespace Ggl {


/**
 * Utility for checking for OpenGL errors.
 */
class ErrorChecker {
public:
	static void checkErrors(const std::string &location);
	static void clearErrors();
private:
	static void report(GLenum error, const std::string &location);
	static std::string toString(GLenum error);
// Constructors
    ErrorChecker();
};

} /* namespace Ggl */
#endif
