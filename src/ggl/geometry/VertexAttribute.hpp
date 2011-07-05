/*
 * VertexAttribute.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_VERTEXATTRIBUTE_HPP
#define GGL_VERTEXATTRIBUTE_HPP
#include "ggl/common.h"
namespace Ggl {


/**
 * @brief Value for a vertex.
 */
class VertexAttribute {
public:
	VertexAttribute();
	VertexAttribute(const std::string &name, GLuint components);
	virtual ~VertexAttribute();
// Getters and setters
	GLuint getCount() const;
	void setCount(GLuint count);
	GLint getLocation() const;
	void setLocation(GLint location);
	std::string getName() const;
	void setName(std::string name);
private:
	std::string name;
	GLint location;
	GLuint count;
};

/**
 * Returns number of components in the attribute.
 */
inline GLuint VertexAttribute::getCount() const {return count;}
inline void VertexAttribute::setCount(GLuint c) {this->count = c;}

/**
 * Returns location of the attribute in the shader program.
 */
inline GLint VertexAttribute::getLocation() const {return location;}
inline void VertexAttribute::setLocation(GLint l) {this->location = l;}

/**
 * Returns name of the attribute.
 */
inline std::string VertexAttribute::getName() const {return name;}
inline void VertexAttribute::setName(std::string name) {this->name = name;}

} /* namespace Ggl */
#endif
