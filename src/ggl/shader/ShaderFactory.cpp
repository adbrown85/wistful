/*
 * ShaderFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/shader/ShaderFactory.hpp"
using namespace std;
using namespace Ggl;

/**
 * Creates a shader factory.
 */
ShaderFactory::ShaderFactory() {
    ;
}

/**
 * Destroys a shader factory and all the shaders it created.
 */
ShaderFactory::~ShaderFactory() {
    
    map<string,GLuint>::iterator it = shaders.begin();
    
    while (it != shaders.end()) {
        glDeleteShader(it->second);
        ++it;
    }
}

/**
 * Creates a shader from a file, guessing its type.
 * 
 * @param filename Path to a file
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
    
    // Load it
    handle = ShaderLoader::load(filename);
    shaders[filename] = handle;
    return handle;
}

/**
 * Creates a shader from a file using a type.
 * 
 * @param filename Path to a file
 * @param type Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @return OpenGL handle to a shader
 */
GLuint ShaderFactory::create(const string &filename, GLenum type) {
    
    map<string,GLuint>::iterator it;
    GLuint handle;
    
    // Check if already made
    it = shaders.find(filename);
    if (it != shaders.end()) {
        return it->second;
    }
    
    // Build it
    handle = ShaderLoader::load(filename, type);
    shaders[filename] = handle;
    return handle;
}
