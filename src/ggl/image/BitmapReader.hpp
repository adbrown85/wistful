/*
 * BitmapReader.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_BITMAPREADER_HPP
#define GGL_BITMAPREADER_HPP
#include <fstream>
#include <cstring>
#include "ggl/common.h"
#include "ggl/image/Image.hpp"
namespace Ggl {


/**
 * @brief Utility for reading a bitmap image into memory.
 */
class BitmapReader {
public:
    BitmapReader();
    virtual ~BitmapReader();
    virtual void read(const std::string &filename);
    virtual Image* toImage();
// Getters and setters
    virtual GLuint getAlignment();
    virtual GLenum getFormat();
    virtual GLuint getSize();
    virtual GLuint getWidth();
    virtual GLuint getHeight();
private:
// Nested classes
    struct BitmapFileHeader;
    struct BitmapInfoHeader;
// Instance variables
    std::ifstream file;
    BitmapFileHeader *fileHeader;
    BitmapInfoHeader *infoHeader;
    GLubyte *pixels;
// Helpers
    void open(const std::string &filename);
    void close();
    void readFileHeader();
    void readInfoHeader();
    void readPixels();
    bool isValidFileHeader();
    bool isValidInfoHeader();
    bool isCompressed();
    bool is24Bit();
// Constructors
    BitmapReader(const BitmapReader&);
    BitmapReader& operator=(const BitmapReader&);
};

/* File header of a bitmap image. */
struct BitmapReader::BitmapFileHeader {
    char bfType[2];
    GLuint bfSize;
    GLushort bfReserved1;
    GLushort bfReserved2;
    GLuint bfOffBits;
};

/* Information header of a bitmap image. */
struct BitmapReader::BitmapInfoHeader {
    GLuint biSize;
    GLuint biWidth;
    GLuint biHeight;
    GLushort biPlanes;
    GLushort biBitCount;
    GLuint biCompression;
    GLuint biSizeImage;
    GLuint biXPelsPerMeter;
    GLuint biYPelsPerMeter;
    GLuint biClrUsed;
    GLuint biClrImportant;
};

} /* namespace Ggl */
#endif
