/*
 * Path.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/system/Path.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates a path.
 * 
 * @param filename Name of a file
 * @throw std::exception if filename is empty
 */
Path::Path(const string &filename) {
    if (filename.empty()) {
        throw Exception("[Path] Filename is empty!");
    } else {
        this->root = createRoot(filename);
        this->parts = createParts(filename);
    }
}

/**
 * Destroys the path.
 */
Path::~Path() {
    ;
}

/**
 * Returns <tt>true</tt> if path is an absolute path.
 */
bool Path::isAbsolute() const {
    return !root.empty();
}

/**
 * Returns <tt>true</tt> if path is a directory.
 */
bool Path::isDirectory() const {
    return parts.empty() || Text::endsWith(parts.back(), '/');
}

/**
 * Returns the path as a string.
 */
string Path::toString() const {
    
    ostringstream ss;
    list<string>::const_iterator it = parts.begin();
    
    // Root
    ss << root;
    
    // Parts
    if (!parts.empty()) {
        it = parts.begin();
        ss << (*it);
        ++it;
        while (it != parts.end()) {
            ss << "/" << (*it);
            ++it;
        }
    }
    
    return ss.str();
}

/* Helpers */

/**
 * Makes the parts of the filename.
 * 
 * @param filename Filename to look in
 * @return List of strings containing the parts
 */
list<string> Path::createParts(const string &filename) {
    
    list<string> tokens = tokenize(filename);
    list<string>::iterator it;
    
    // Check for Unix root
    if (tokens.empty()) {
        return tokens;
    }
    
    // Check for Windows root
    it = tokens.begin();
    if (isWindowsRoot(*it)) {
        tokens.erase(it);
    }
    
    // Check for directory
    if (Text::endsWith(filename, '/')) {
        tokens.back() += '/';
    }
    
    return tokens;
}

/**
 * Makes the root of the path from a filename.
 * 
 * @param filename Filename to look in
 * @return String containing the root, or the empty string
 */
string Path::createRoot(const string &filename) {
    if (hasUnixRoot(filename)) {
        return "/";
    } else if (hasWindowsRoot(filename)) {
        return filename.substr(0, 2) + '/';
    } else {
        return "";
    }
}

/**
 * Checks if a string has a Unix root.
 * 
 * @param string String to look in
 * @return <tt>true</tt> if string starts with a Unix root
 */
bool Path::hasUnixRoot(const string &str) {
    return str[0] == '/';
}

/**
 * Checks if a string has a Windows root.
 * 
 * @param str String to look in
 * @return <tt>true</tt> if string starts with a Windows root
 */
bool Path::hasWindowsRoot(const string &str) {
    if (str.length() < 2) {
        return false;
    } else {
        return isalpha(str[0]) && (str[1] == ':');
    }
}

/**
 * Checks if a character is a path separator.
 * 
 * @param c Character to check
 * @return <tt>true</tt> if the character is a path separator
 */
bool Path::isSeparator(char c) {
    return (c == '/') || (c == '\\');
}

/**
 * Checks if a string is a Windows root.
 * 
 * @param str String to check
 * @return <tt>true</tt> if string is a Windows root
 */
bool Path::isWindowsRoot(const string &str) {
    return (str.length() == 2) && (isalpha(str[0])) && (str[1] == ':');
}

/**
 * Breaks up a filename into its parts.
 * 
 * @param filename Name of a file
 * @return List of tokens in filename
 */
list<string> Path::tokenize(const string &filename) {
    
    int len;                 // Length of buffer
    char *buffer;            // Character buffer storing filename
    char *token;             // Pointer to token in buffer
    list<string> tokens;     // List storing each token
    
    // Copy filename into buffer
    len = filename.length() + 1;
    buffer = new char[len];
    strcpy(buffer, filename.c_str());
    
    // Break up buffer into tokens
    token = strtok(buffer, "/\\");
    while (token != NULL) {
        tokens.push_back(token);
        token = strtok(NULL, "/\\");
    }
    
    // Finish
    delete[] buffer;
    return tokens;
}