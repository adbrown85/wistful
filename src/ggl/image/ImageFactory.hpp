/*
 * ImageFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_IMAGEFACTORY_HPP
#define GGL_IMAGEFACTORY_HPP
#include "ggl/common.h"
#include "ggl/image/Image.hpp"
#include "ggl/image/BitmapReader.hpp"
#include "ggl/system/Text.hpp"
namespace Ggl {


/**
 * @brief Creates an image of the appropriate type.
 */
class ImageFactory {
public:
    static Image* create(const std::string &filename);
private:
    static Image* createBitmap(const std::string &filename);
    static std::string findExtension(const std::string &filename);
};

} /* namespace Ggl */
#endif
