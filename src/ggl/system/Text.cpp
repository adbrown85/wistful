/*
 * Text.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/system/Text.hpp"
using namespace std;
using namespace Ggl;

/**
 * Finds the number of occurrences of a character in a string.
 * 
 * @param str String to look in
 * @param c Character to look for
 * @return Number of times character appears in string
 */
int Text::count(const string &str, char c) {
    
    int len = str.length();
    int times = 0;
    
    for (size_t i=0; i<len; ++i) {
        if (str[i] == c) {
            ++times;
        }
    }
    return times;
}

/**
 * Checks if a character is at the end of a string.
 * 
 * @param str String to look in
 * @param c Character to look for
 * @return <tt>true</tt> if the character is at the end
 */
bool Text::endsWith(const string &str, char c) {
    
    int last = str.length() - 1;
    
    return str[last] == c;
}

/**
 * Finds index of first character in a string that cannot be part of a word.
 * 
 * @param str String to search
 * @param idx Index to start from
 * @return Index of character, or -1 if not found
 */
int Text::findFirstNotWordCharacter(const string &str, int idx) {
    
    int len = str.length();
    
    for (int i=idx; i<len; ++i) {
        if (str[i] != '_' && !isalpha(str[i])) {
            return i;
        }
    }
    return -1;
}

/**
 * Finds the first word in a string.
 * 
 * @param str String to search
 * @param idx Index to start searching from
 * @return Start of the word and its length
 */
pair<int,int> Text::findFirstWord(const string &str, int idx) {
    
    int beg, end;
    
    // Find start
    beg = findFirstWordCharacter(str, idx);
    if (beg == -1) {
        return pair<int,int>(-1,0);
    }
    
    // Find end
    end = findFirstNotWordCharacter(str, beg+1);
    if (end == -1) {
        end = str.length();
    }
    
    return pair<int,int>(beg, end-beg);
}

/**
 * Finds index of first character in a string that can be part of a word.
 * 
 * @param str String to search
 * @param idx Index to start from
 * @return Index of character, or -1 if not found
 */
int Text::findFirstWordCharacter(const string &str, int idx) {
    
    int len = str.length();
    
    for (int i=idx; i<len; ++i) {
        if (str[i] == '_' || isalpha(str[i])) {
            return i;
        }
    }
    return -1;
}

/**
 * Creates a string to use for indentation.
 * 
 * @param times Number of times to indent
 * @return String containing two spaces for each indent
 */
string Text::indent(int times) {
    
    ostringstream stream;
    
    for (int i=0; i<times; ++i) {
        stream << "  ";
    }
    return stream.str();
}

/**
 * Creates a copy of a string with certain words substituted.
 * 
 * @param str String to look in
 * @param words Mapping of words to their replacements
 * @return String with the replacements made, or just a copy
 */
string Text::replace(const string &str, map<string,string> &words) {
    
    map<string,string>::iterator it;
    pair<int,int> bounds;
    string copy = str;
    string value;
    string word;
    
    bounds = findFirstWord(copy, 0);
    while (bounds.first != -1) {
        word = copy.substr(bounds.first, bounds.second);
        it = words.find(word);
        if (it != words.end()) {
            value = it->second;
            copy = copy.replace(bounds.first, bounds.second, value);
            bounds = findFirstWord(copy, bounds.first + value.length());
        } else {
            bounds = findFirstWord(copy, bounds.first + word.length());
        }
    }
    return copy;
}

/**
 * Breaks a string into two pieces around a character.
 * 
 * @param str String to break
 * @param c Character to look for
 * @return Pieces before and after character
 */
pair<string,string> Text::split(const string &str, char c) {
    
    size_t idx = str.find(c);
    pair<string,string> couple;
    
    couple.first = str.substr(0, idx);
    couple.second = str.substr(idx + 1);
    return couple;
}

/**
 * Removes spaces at the beginning of a string.
 * 
 * @param str String with spaces to remove
 * @return Copy of string with no spaces at the beginning
 */
string Text::stripLeadingSpaces(const string &str) {
    
    size_t idx = str.find_first_not_of(" \t");
    size_t len = str.length();
    
    return (idx > len) ? "" : str.substr(idx);
}

/**
 * Removes spaces at the end of a string.
 * 
 * @param str String with spaces to remove
 * @return Copy of string with no spaces at the end
 */
string Text::stripTrailingSpaces(const string &str) {
    
    int i, last;
    
    last = str.length() - 1;
    for (i=last; i>=0; --i) {
        if (!isspace(str[i])) {
            break;
        }
    }
    return str.substr(0, i+1);
}

/**
 * Converts a string to all lowercase.
 * 
 * @param str String to convert
 * @return Converted string
 */
string Text::toLower(const string &str) {
    
    int len = str.length();
    string copy = str;
    
    // Convert each character
    for (int i=0; i<len; ++i) {
        copy[i] = tolower(str[i]);
    }
    return copy;
}

/**
 * Converts a string to all uppercase.
 * 
 * @param str String to convert
 * @return Converted string
 */
string Text::toUpper(const string &str) {
    
    int len = str.length();
    string copy = str;
    
    // Convert each character
    for (int i=0; i<len; ++i) {
        copy[i] = toupper(str[i]);
    }
    return copy;
}

/**
 * Removes characters at the beginning and of a string.
 * 
 * @param str String to remove characters from
 * @param c Characters to remove
 * @return Copy of string with characters removed
 */
string Text::trim(const string &str, const string &c) {
    
    size_t beg = str.find_first_not_of(c);
    size_t end = str.find_last_not_of(c);
    size_t len = end - beg + 1;
    
    return str.substr(beg, len);
}

