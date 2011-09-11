/*
 * ShaderBuilder.cpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/config.h"
#include "ggl/shader/ShaderBuilder.hpp"
using namespace std;
using namespace Edo;
using namespace Ggl;

/**
 * Constructs a shader builder.
 */
ShaderBuilder::ShaderBuilder() {
    ;
}

/**
 * Destroys a shader builder.
 */
ShaderBuilder::~ShaderBuilder() {
    ;
}

void ShaderBuilder::addLine(const string &line) {
    lines.push_back(line);
}

void ShaderBuilder::addLines(const list<string> &lines) {
    
    list<string>::const_iterator it = lines.begin();
    
    while (it != lines.end()) {
        addLine(*it);
        ++it;
    }
}

void ShaderBuilder::addLines(const vector<string> &lines) {
    
    vector<string>::const_iterator it = lines.begin();
    
    while (it != lines.end()) {
        addLine(*it);
        ++it;
    }
}

GLuint ShaderBuilder::toShader(GLenum type) {
    
    GLuint handle = create(type);
    
    load(handle, lines);
    compile(handle);
    
    lines.clear();
    
    return handle;
}

//----------------------------------------
// Helpers
//

/**
 * Compiles a shader.
 * 
 * @param handle Handle to OpenGL shader 
 * @throw std::exception if shader does not compile
 */
void ShaderBuilder::compile(GLuint handle) {
    
    GLint compiled;
    
    glCompileShader(handle);
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        cerr << getLog(handle);
        throw Exception("[ShaderBuilder] Shader did not compile!");
    }
}

/**
 * Requests a handle to a new GLSL shader of the correct type.
 * 
 * @param type Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @return Handle to new OpenGL shader
 * @throw std::exception if type is not supported
 */
GLuint ShaderBuilder::create(GLenum type) {
    switch (type) {
    case GL_FRAGMENT_SHADER:
    case GL_VERTEX_SHADER:
        return glCreateShader(type);
    default:
        throw Exception("[Shader] Type not supported!");
    }
}

/**
 * Retrieves the log of a shader.
 * 
 * @param handle Handle to shader
 * @return String containing log
 */
string ShaderBuilder::getLog(GLuint handle) {
    
    GLchar *arr;
    GLsizei count;
    GLsizei returned;
    string str;
    
    // Allocate
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &count);
    arr = new GLchar[count + 1];
    
    // Retrieve
    glGetShaderInfoLog(handle, count, &returned, arr);
    arr[returned] = '\0';
    str = arr;
    
    // Finish
    delete[] arr;
    return str;
}

/**
 * Loads a file into the shader's source array and passes it to OpenGL.
 * 
 * @param handle Internal OpenGL identifier for shader
 * @param lines Lines of shader
 */
void ShaderBuilder::load(GLuint handle, const vector<string> &lines) {
    
    int len = lines.size();
    const char **source = new const char*[len];
    
    // Copy to source array
    for (int i=0; i<len; ++i) {
        source[i] = lines[i].c_str();
    }
    
    // Pass to OpenGL
    glShaderSource(handle, len, source, NULL);
}
