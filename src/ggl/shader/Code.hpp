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
    void clear();
// Accessors
    iterator begin();
    iterator end();
    CodeLine getLine(int number) const;
    size_t size() const;
private:
    std::vector<CodeLine> lines;
};

} /* namespace Ggl */
#endif
