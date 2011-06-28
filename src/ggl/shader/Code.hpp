/*
 * Code.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_CODE_HPP
#define GGL_CODE_HPP
#include <vector>
#include "ggl/common.h"
namespace Ggl {


/* Line of code. */
struct CodeLine {
    std::string filename;
    std::string text;
    int number;
};


/**
 * @brief Source code loaded from multiple files.
 */
class Code {
public:
    typedef std::vector<CodeLine>::iterator iterator;
public:
    void add(const CodeLine &line);
    void add(const std::string &filename, int number, const std::string &text);
    iterator begin();
    iterator end();
    void clear();
// Accessors
    size_t size() const;
    CodeLine getLine(int number) const;
private:
    std::vector<CodeLine> lines;
};

/** @return Iterator to the beginning of the code lines. */
inline Code::iterator Code::begin() {return lines.begin();}

/** @return Iterator to the end of the code lines. */
inline Code::iterator Code::end() {return lines.end();}

/** Clears all the lines stored. */
inline void Code::clear() {lines.clear();}

/** @return Number of lines stored. */
inline size_t Code::size() const {return lines.size();}

/** @return Line of code at index equal to @e number. */
inline CodeLine Code::getLine(int number) const {return lines[number];}

} /* namespace Ggl */
#endif
