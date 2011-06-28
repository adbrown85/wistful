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
 */
void Code::addLine(const CodeLine &line) {
    lines.push_back(line);
}

/**
 * Adds a line to the source code.
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
 * Returns an iterator to the beginning of the code lines.
 */
Code::iterator Code::begin() {
    return lines.begin();
}

/**
 * Returns an iterator to the end of the code lines.
 */
Code::iterator Code::end() {
    return lines.end();
}

/**
 * Clears all the stored lines.
 */
void Code::clearLines() {
    lines.clear();
}

/**
 * Returns number of stored lines stored.
 */
size_t Code::size() const {
    return lines.size();
}

/**
 * Returns line of code at index equal to @e number.
 */
CodeLine Code::getLine(int number) const {
    return lines[number];
}
