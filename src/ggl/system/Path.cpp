/*
 * Path.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/system/Path.hpp"
using namespace std;
using namespace Edo;
using namespace Ggl;

/**
 * Creates a path from a string.
 * 
 * @param filename Name of file
 * @return Path instance
 * @throw std::exception if filename is empty
 */
Path Path::fromString(const string &filename) {
    
    if (filename.empty()) {
        throw Exception("[Path] Filename is empty!");
    }
    
    string root = createRoot(filename);
    list<string> parts = createParts(filename);
    bool directory = endsWithSeparator(filename);
    
    return Path(root, parts, directory);
}

/**
 * Creates a path.
 * 
 * @param root Root of path
 * @param parts Parts of path
 * @param directory <tt>true</tt> if path is a directory
 */
Path::Path(const string &root,
           const list<string> &parts,
           bool directory) {
    this->root = root;
    this->parts = parts;
    this->directory = directory;
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
    return directory;
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
    
    // Directory
    if (directory && !parts.empty()) {
        ss << "/";
    }
    
    return ss.str();
}

/* Utilities */

Path Path::basename(const Path &path) {
    
    string last;
    list<string> parts;
    
    if (path.isDirectory()) {
        return Path("", parts, false);
    }
    
    last = path.parts.back();
    parts.push_back(last);
    
    return Path("", parts, false);
    
}

/**
 * Finds directory section of a path.
 * 
 * @param path Path to find directory section of
 * @return Directory section of path
 */
Path Path::dirname(const Path &path) {
    
    if (path.isDirectory()) {
        return path;
    }
    
    string root = path.root;
    list<string> parts = path.parts;
    bool directory = true;
    
    parts.pop_back();
    
    return Path(root, parts, directory);
}

/**
 * Combines two paths together.
 * 
 * @param folder Path to a directory
 * @param file Path to a file
 * @return Path to the file relative to the directory
 * @throw std::exception if first path is not a directory
 * @throw std::exception if second path is not a file
 */
Path Path::locate(const Path &folder, const Path &file) {
    
    string root;
    list<string> parts;
    list<string>::const_iterator it;
    
    // Validate
    if (!folder.isDirectory()) {
        throw Exception("[Path] First path is not a directory!");
    } else if (file.isDirectory()) {
        throw Exception("[Path] Second path is not a file!");
    } else if (file.isAbsolute()) {
        return file;
    }
    
    // First copy directory path's data
    root = folder.root;
    parts = folder.parts;
    
    // Merge relative path's parts into copy
    it = file.parts.begin();
    while (it != file.parts.end()) {
        if (((*it) != "..")) {
            parts.push_back((*it));
        } else if (!parts.empty()) {
            parts.pop_back();
        }
        ++it;
    }
    
    return Path(root, parts, false);
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
 * Checks if a string ends with a path separator.
 * 
 * @param str String to check
 * @return <tt>true</tt> if last character is a slash
 */
bool Path::endsWithSeparator(const string &str) {
    return Text::endsWith(str, '/') || Text::endsWith(str, '\\');
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
