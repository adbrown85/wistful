/*
 * ShaderLoader.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/shader/ShaderLoader.hpp"
using namespace std;
using namespace Edo;
using namespace Ggl;

/**
 * Builds a shader from a file, guessing the type.
 * 
 * @param filename Path to a file
 * @throw std::exception if file extension not recognized
 */
GLuint ShaderLoader::load(const string &filename) {
    return load(filename, findType(filename));
}

/**
 * Builds a shader from a file using a type.
 * 
 * @param filename Path to a file
 * @param type Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @throw std::exception if type not recognized
 * @throw std::exception if file cannot be opened
 */
GLuint ShaderLoader::load(const string &filename, GLenum type) {
    
    ShaderBuilder sb;
    Code code = read(filename);
    Code::iterator it = code.begin();
    
    while (it != code.end()) {
        sb.addLine(it->text);
        ++it;
    }
    
    return sb.toShader(type);
}

//----------------------------------------
// Helpers
//

/**
 * Determines the extension of a file.
 * 
 * @param filename Name of file
 * @return Text after period converted to lowercase
 */
string ShaderLoader::findExtension(const std::string &filename) {
    
    size_t pos = filename.rfind('.');
    string extension = filename.substr(pos + 1);
    
    return Text::toLower(extension);
}

/**
 * Determines the shader type of a file by an extension.
 * 
 * @param filename Name of a file
 * @return Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @throw std::exception if file extension not recognized
 */
GLenum ShaderLoader::findType(const std::string &filename) {
    
    string extension = findExtension(filename);
    
    if (extension == "frag") {
        return GL_FRAGMENT_SHADER;
    } else if (extension == "vert") {
        return GL_VERTEX_SHADER;
    } else {
        throw Exception("[ShaderLoader] Extension not recognized!");
    }
}

/**
 * Reads a file into memory.
 * 
 * @param filename File to read
 * @return Code from file
 */
ShaderLoader::Code ShaderLoader::read(const string &filename) {
    
    Preprocessor preprocessor;
    
    preprocessor.parse(filename);
    return preprocessor.getCode();
}

// NESTED CLASSES

/**
 * Adds a line to the source code.
 * 
 * @param filename Name of file line originated from
 * @param number Line number of original file
 * @param text Characters in line
 */
void ShaderLoader::Code::addLine(const string &filename,
                                 int number,
                                 const string &text) {
    
    Line line;
    
    // Make line
    line.filename = filename;
    line.number = number;
    line.text = text;
    
    // Add it
    lines.push_back(line);
}

/**
 * Returns an iterator to the beginning of the code.
 */
ShaderLoader::Code::iterator ShaderLoader::Code::begin() {
    return lines.begin();
}

/**
 * Returns an iterator past the end of the code.
 */
ShaderLoader::Code::iterator ShaderLoader::Code::end() {
    return lines.end();
}

/**
 * Removes all the lines from the code.
 */
void ShaderLoader::Code::clearLines() {
    lines.clear();
}

/**
 * Returns number of lines in the code.
 */
size_t ShaderLoader::Code::size() const {
    return lines.size();
}

/**
 * Returns a line from the code.
 * 
 * @param number Index of line in code
 */
ShaderLoader::Line ShaderLoader::Code::getLine(int number) const {
    return lines[number];
}

/**
 * Constructs an empty preprocessor.
 */
ShaderLoader::Preprocessor::Preprocessor() {
    ;
}

/**
 * Returns <tt>true</tt> if the line is an include pragma.
 */
bool ShaderLoader::Preprocessor::isInclude(const string &line) {
    return line.substr(0,8) == "#include";
}

/**
 * Loads a file into the code.
 * 
 * @throw BasicException if the file cannot be opened.
 */
void ShaderLoader::Preprocessor::load(const string &filename) {
    
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
void ShaderLoader::Preprocessor::onInclude(const string &line) {
    
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
void ShaderLoader::Preprocessor::onLine(const string &filename,
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
void ShaderLoader::Preprocessor::parse(const string &filename) {
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
string ShaderLoader::Preprocessor::stripComments(const string &line,
                                                 bool &inComment) {
    
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
ShaderLoader::Code ShaderLoader::Preprocessor::getCode() const {
    return code;
}

/**
 * Finds the text after a character in a string.
 * 
 * @param str String to look in
 * @param c Character to look for
 * @return Text after the character
 */
string ShaderLoader::Preprocessor::after(const string &str, char c) {
    
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
string ShaderLoader::Preprocessor::trim(const string &str,
                                        const string &characters) {
    
    size_t beg = str.find_first_of(characters);
    size_t end = str.find_last_of(characters);
    size_t len = end - beg + 1;
    
    return str.substr(beg, len);
}

