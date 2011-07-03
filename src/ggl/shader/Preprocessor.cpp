/*
 * Preprocessor.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/shader/Preprocessor.hpp"
using namespace std;
using namespace Ggl;


/**
 * Returns <tt>true</tt> if the line is an include pragma.
 */
bool Preprocessor::isInclude(const string &line) {
    return line.substr(0,8) == "#include";
}

/**
 * Loads a file into the code.
 * 
 * @throw BasicException if the file cannot be opened.
 */
void Preprocessor::load(const string &filename) {
    
    bool inComment;
    ifstream file;
    int number;
    string text;
    
    // Open file
    file.open(filename.c_str());
    if (!file) {
        throw Exception("[Preprocessor] Could not open file!");
    }
    
    // Load into vector
    inComment = false;
    number = 0;
    getline(file, text);
    while (file) {
        onLine(filename, ++number, text, inComment);
        getline(file, text);
    }
}

/**
 * Loads an included file if it wasn't already.
 * 
 * @param line Line with include on it
 */
void Preprocessor::onInclude(const string &line) {
    
    string argument, filename;
    set<string>::iterator it;
    
    // Find filename in pragma
    argument = after(line, ' ');
    filename = trim(argument, "\"\'");
    
    // Check if already loaded
    it = includes.find(filename);
    if (it != includes.end()) {
        return;
    } else {
        includes.insert(filename);
    }
    
    // Make it relative to base file and load it
    Path p1 = Path::dirname(Path::fromString(this->filename));
    Path p2 = Path::fromString(filename);
    Path p3 = Path::locate(p1, p2);
    load(p3.toString());
}

/**
 * Adds a line after filtering it.
 * 
 * @param filename Path to file
 * @param number Number of line
 * @param text Characters in line
 * @param inComment Set to <tt>true</tt> if comment encountered
 */
void Preprocessor::onLine(const string &filename,
                          int number,
                          string &text,
                          bool &inComment) {
    
    // Strip comments and trailing space
    text = stripComments(text, inComment);
    text = Text::stripTrailingSpaces(text);
    if (text.empty()) {
        return;
    }
    
    // Check if in comment
    if (inComment)
        return;
    
    // Add line unless an include
    if (isInclude(text)) {
        onInclude(text);
    } else {
        code.addLine(filename, number, text.append("\n"));
    }
}

/**
 * Loads a file.
 * 
 * @param filename Path to file to parse
 */
void Preprocessor::parse(const string &filename) {
    this->filename = filename;
    code.clearLines();
    includes.clear();
    load(filename);
}

/**
 * Removes comments from a line.
 * 
 * @param line Line to remove comments from
 * @param inComment Set to <tt>true</tt> if a comment is found
 */
string Preprocessor::stripComments(const string &line, bool &inComment) {
    
    int length;
    ostringstream buffer;
    
    length = line.length();
    for (int i=0; i<length; ++i) {
        
        // Single-line comment
        if (line[i] == '/' && line[i+1] == '/') {
            break;
        }
        
        // Start of multi-line comment
        if (line[i] == '/' && line[i+1] == '*') {
            inComment = true;
            ++i;
            continue;
        }
        
        // End of multi-line comment
        else if (line[i] == '*' && line[i+1] == '/') {
            inComment = false;
            ++i;
            continue;
        }
        
        // In comment
        if (inComment) {
            continue;
        }
        
        // Normal
        buffer << line[i];
    }
    return buffer.str();
}

/**
 * Returns the lines of the file that are actual code.
 */
Code Preprocessor::getCode() const {
    return code;
}

/**
 * Finds the text after a character in a string.
 * 
 * @param str String to look in
 * @param c Character to look for
 * @return Text after the character
 */
string Preprocessor::after(const string &str, char c) {
    
    size_t pos = str.find(c);
    
    return str.substr(pos + 1);
}

/**
 * Takes the text between characters in a string.
 * 
 * @param str String to look in
 * @param characters Characters to look for
 * @return Copy of text between the characters
 */
string Preprocessor::trim(const string &str,
                          const string &characters) {
    
    size_t beg = str.find_first_of(characters);
    size_t end = str.find_last_of(characters);
    size_t len = end - beg + 1;
    
    return str.substr(beg, len);
}
