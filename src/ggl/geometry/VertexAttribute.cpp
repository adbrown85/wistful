/*
 * VertexAttribute.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/geometry/VertexAttribute.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates a vertex attribute.
 */
VertexAttribute::VertexAttribute() {
	this->name = "";
	this->count = 4;
	this->location = -1;
}

/**
 * Creates a vertex attribute.
 * 
 * @param name Name of the attribute
 * @param count Number of components in attribute
 */
VertexAttribute::VertexAttribute(const string &name, GLuint count) {
	this->name = name;
	this->count = count;
	this->location = -1;
}

/**
 * Destroys the vertex attribute.
 */
VertexAttribute::~VertexAttribute() {
	;
}
