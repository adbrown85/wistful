/*
 * Text.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_TEXT_HPP
#define GGL_TEXT_HPP
#include <sstream>
#include "ggl/common.h"
namespace Ggl {


/**
 * @brief Utility for working with strings.
 */
class Text {
    typedef std::map<std::string,std::string> stringmap_t;
    typedef std::pair<int,int> intpair_t;
    typedef std::pair<std::string,std::string> stringpair_t;
public:
    static int count(const std::string &str, char c);
    static bool endsWith(const std::string &str, char c);
    static int findFirstNotWordCharacter(const std::string &str, int idx=0);
    static intpair_t findFirstWord(const std::string &str, int idx=0);
    static int findFirstWordCharacter(const std::string &str, int idx=0);
    static std::string indent(int times);
    static std::string replace(const std::string &str, stringmap_t &words);
    static stringpair_t split(const std::string &str, char c);
    static std::string stripLeadingSpaces(const std::string &str);
    static std::string stripTrailingSpaces(const std::string &str);
    static std::string toLower(const std::string &str);
    static std::string toUpper(const std::string &str);
    static std::string trim(const std::string &str, const std::string &c=" ");
};

} /* namespace Ggl */
#endif
