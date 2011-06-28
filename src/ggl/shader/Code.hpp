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
    void addLine(const CodeLine &line);
    void addLine(const std::string &f, int n, const std::string &t);
    void clearLines();
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
