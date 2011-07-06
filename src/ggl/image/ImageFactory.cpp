/*
 * ImageFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/image/ImageFactory.hpp"
using namespace std;
using namespace Ggl;


/**
 * Creates an image from a file.
 * 
 * @param filename Name of an image file
 * @return Pointer to a new image
 * @throw std::exception if image type not supported
 * @throw std::exception if image could not be read
 */
Image* ImageFactory::create(const string &filename) {
    
    string extension = findExtension(filename);
    
    if (extension == "bmp") {
        return createBitmap(filename);
    } else {
        throw Exception("[ImageFactory] Image type not supported!");
    }
}

//----------------------------------------
// Helpers
//

/**
 * Creates a bitmap image from a file.
 * 
 * @param filename Name of a bitmap image
 * @return Pointer to a new bitmap image
 * @throw std::exception if image could not be read
 */
Image* ImageFactory::createBitmap(const string &filename) {
    
    BitmapReader reader;
    
    reader.read(filename);
    return reader.toImage();
}

/**
 * Determines the extension of a file.
 * 
 * @param filename Name of a file
 * @return Suffix after last period
 */
string ImageFactory::findExtension(const string &filename) {
    
    size_t index = filename.rfind('.');
    string extension = filename.substr(index);
    
    return Text::toLower(extension);
}
