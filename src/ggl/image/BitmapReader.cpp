/*
 * BitmapReader.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/image/BitmapReader.hpp"
using namespace std;
using namespace Edo;
using namespace Ggl;

/**
 * Constructs a new bitmap image reader.
 */
BitmapReader::BitmapReader() {
    this->pixels = NULL;
    this->infoHeader = new BitmapInfoHeader();
    this->fileHeader = new BitmapFileHeader();
}

/**
 * Destroys the bitmap image reader.
 */
BitmapReader::~BitmapReader() {
    delete[] pixels;
    delete infoHeader;
    delete fileHeader;
}

/**
 * Reads an image into memory.
 * 
 * @throw std::exception if file cannot be read
 * @throw std::exception if file header is invalid
 * @throw std::exception if info header is invalid
 * @throw std::exception if bitmap is compressed
 * @throw std::exception if bitmap is not 24-bit
 * @throw std::exception if incorrect number of pixels were read
 */
void BitmapReader::read(const string &filename) {
    try {
        open(filename);
        readFileHeader();
        readInfoHeader();
        readPixels();
        close();
    } catch (std::exception &e) {
        close();
        throw Exception(e.what());
    }
}

/**
 * Creates an image from what was read.
 */
Image* BitmapReader::toImage() {
    return new Image(
            getAlignment(),
            getFormat(),
            pixels,
            getSize(),
            getWidth(),
            getHeight());
}

// HELPERS

/**
 * Opens the file.
 * 
 * @throw std::exception if file cannot be read
 */
void BitmapReader::open(const string &filename) {
    file.open(filename.c_str(), ios_base::binary);
    if (!file) {
        throw Exception("[BitmapReader] File could not be opened!");
    }
}

/**
 * Closes the file.
 */
void BitmapReader::close() {
    file.close();
}

/**
 * Returns true if any info header fields indicate the data is compressed.
 */
bool BitmapReader::isCompressed() {
    return infoHeader->biCompression != 0;
}

/**
 * Returns true if info header fields indicate the data is 24-bit.
 */
bool BitmapReader::is24Bit() {
    return infoHeader->biBitCount == 24
            && infoHeader->biClrUsed == 0
            && infoHeader->biClrImportant == 0;
}

/**
 * Returns true if the file header is valid.
 */
bool BitmapReader::isValidFileHeader() {
    return fileHeader->bfType[0] == 'B'
            && fileHeader->bfType[1] == 'M'
            && fileHeader->bfReserved1 == 0
            && fileHeader->bfReserved2 == 0;
}

/**
 * Returns true if the info header is valid.
 */
bool BitmapReader::isValidInfoHeader() {
    return infoHeader->biSize == 40
            && infoHeader->biWidth > 0
            && infoHeader->biHeight > 0
            && infoHeader->biPlanes == 1;
}

/**
 * Reads just the file header section.
 * 
 * @throw std::exception if file header is invalid
 */
void BitmapReader::readFileHeader() {
    
    file.read((char*) &fileHeader->bfType, 2);
    file.read((char*) &fileHeader->bfSize, 4);
    file.read((char*) &fileHeader->bfReserved1, 2);
    file.read((char*) &fileHeader->bfReserved2, 2);
    file.read((char*) &fileHeader->bfOffBits, 4);
    
    if (!isValidFileHeader()) {
        throw Exception("[BitmapReader] Not a valid bitmap file header!");
    }
}

/**
 * Reads just the info header section.
 * 
 * @throw std::exception if info header is invalid
 * @throw std::exception if bitmap is compressed
 * @throw std::exception if bitmap is not 24-bit
 */
void BitmapReader::readInfoHeader() {
    
    file.read((char*) &infoHeader->biSize, 4);
    file.read((char*) &infoHeader->biWidth, 4);
    file.read((char*) &infoHeader->biHeight, 4);
    file.read((char*) &infoHeader->biPlanes, 2);
    file.read((char*) &infoHeader->biBitCount, 2);
    file.read((char*) &infoHeader->biCompression, 4);
    file.read((char*) &infoHeader->biSizeImage, 4);
    file.read((char*) &infoHeader->biXPelsPerMeter, 4);
    file.read((char*) &infoHeader->biYPelsPerMeter, 4);
    file.read((char*) &infoHeader->biClrUsed, 4);
    file.read((char*) &infoHeader->biClrImportant, 4);
    
    if (!isValidInfoHeader()) {
        throw Exception("[BitmapReader] Not a valid bitmap info header!");
    } else if (isCompressed()) {
        throw Exception("[BitmapReader] Only supports uncompressed data.");
    } else if (!is24Bit()) {
        throw Exception("[BitmapReader] Only supports 24-bit data.");
    }
}

/**
 * Reads the pixel data into memory.
 * 
 * @throw std::exception if incorrect number of pixels were read
 */
void BitmapReader::readPixels() {
    
    size_t size = getSize();
    
    if (pixels != NULL) {
        delete[] pixels;
    }
    
    pixels = new GLubyte[size];
    file.read((char*) pixels, size);
    
    if (file.gcount() != size) {
        throw Exception("[BitmapReader] All pixels could not be read!");
    }
}

// GETTERS AND SETTERS

/**
 * Returns number of bytes that row length should be multiples of.
 */
GLuint BitmapReader::getAlignment() {
    return 4;
}

/**
 * Returns format of the image (GL_BGR).
 */
GLenum BitmapReader::getFormat() {
    return GL_BGR;
}

/**
 * Returns total number of bytes required to hold the image.
 */
GLuint BitmapReader::getSize() {
    return infoHeader->biSizeImage;
}

/**
 * Returns number of pixels in the X direction.
 */
GLuint BitmapReader::getWidth() {
    return infoHeader->biWidth;
}

/**
 * Returns number of pixels in the Y direction.
 */
GLuint BitmapReader::getHeight() {
    return infoHeader->biHeight;
}
