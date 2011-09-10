/*
 * Model.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_MODEL_HPP
#define GGL_MODEL_HPP
#include "ggl/common.h"
namespace Ggl {


/**
 * Polygonal geometry that can be rendered.
 * 
 * @ingroup geometry
 */
class Model {
public:
    Model();
    virtual ~Model();
    virtual void render() = 0;
private:
// Constructors
    Model(const Model&);
    Model& operator=(const Model&);
};

} /* namespace Ggl */
#endif
