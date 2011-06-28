/*
 * Code.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/shader/Code.hpp"
using namespace std;
using namespace Ggl;

/**
 * Adds a line to the source code.
 * 
 * @param line Line to add
 */
void Code::addLine(const CodeLine &line) {
    lines.push_back(line);
}

/**
 * Adds a line to the source code.
 * 
 * @param filename Name of file line originated from
 * @param number Line number of original file
 * @param text Characters in line
 */
void Code::addLine(const string &filename,
                   int number,
                   const string &text) {
    
    CodeLine line;
    
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
Code::iterator Code::begin() {
    return lines.begin();
}

/**
 * Returns an iterator past the end of the code.
 */
Code::iterator Code::end() {
    return lines.end();
}

/**
 * Removes all the lines from the code.
 */
void Code::clearLines() {
    lines.clear();
}

/**
 * Returns number of lines in the code.
 */
size_t Code::size() const {
    return lines.size();
}

/**
 * Returns a line from the code.
 * 
 * @param number Index of line in code
 */
CodeLine Code::getLine(int number) const {
    return lines[number];
}
