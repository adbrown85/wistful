/*
 * ShaderFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/shader/ShaderFactory.hpp"
using namespace std;
using namespace Ggl;

/* Static fields */
map<string,GLuint> ShaderFactory::shaders;

/**
 * Creates a shader.
 * 
 * @param filename Name of a file
 * @return OpenGL handle to a shader
 */
GLuint ShaderFactory::create(const string &filename) {
	
	map<string,GLuint>::iterator it;
	GLuint handle;
	
	// Check if already made
	it = shaders.find(filename);
	if (it != shaders.end()) {
		return it->second;
	}
	
	// Build it
	handle = ShaderBuilder::build(filename);
	shaders[filename] = handle;
	return handle;
}

/**
 * Creates a shader.
 * 
 * @param type Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @param filename Name of a file
 * @return OpenGL handle to a shader
 */
GLuint ShaderFactory::create(GLenum type, const string &filename) {
	
	map<string,GLuint>::iterator it;
	GLuint handle;
	
	// Check if already made
	it = shaders.find(filename);
	if (it != shaders.end()) {
		return it->second;
	}
	
	// Build it
	handle = ShaderBuilder::build(type, filename);
	shaders[filename] = handle;
	return handle;
}
