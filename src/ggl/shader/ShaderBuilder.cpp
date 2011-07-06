/*
 * ShaderBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/shader/ShaderBuilder.hpp"
using namespace std;
using namespace Ggl;

/**
 * Builds a shader from a file.
 * 
 * @param filename Name of a file
 * @throw std::exception if file extension not recognized
 */
int ShaderBuilder::build(const string &filename) {
    return build(findType(filename), filename);
}

/**
 * Builds a shader from a type and file.
 * 
 * @param type Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @param filename Name of file
 * @throw std::exception if type not recognized
 * @throw std::exception if file cannot be opened
 */
int ShaderBuilder::build(GLenum type, const string &filename) {
    
    int handle = create(type);
    Code code = read(filename);
    
    load(handle, code);
    compile(handle);
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
void ShaderBuilder::compile(int handle) {
    
    GLint compiled;
    
    glCompileShader(handle);
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        cerr << findLog(handle);
        throw Exception(findLog(handle));
    }
}

/**
 * Requests a handle to a new GLSL shader of the correct type.
 * 
 * @param type Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @return Handle to new OpenGL shader
 * @throw std::exception if type is not supported
 */
int ShaderBuilder::create(GLenum type) {
    switch (type) {
    case GL_FRAGMENT_SHADER:
    case GL_VERTEX_SHADER:
        return glCreateShader(type);
    default:
        throw Exception("[Shader] Type not supported!");
    }
}

/**
 * Determines the extension of a file.
 * 
 * @param filename Name of file
 * @return Text after period converted to lowercase
 */
string ShaderBuilder::findExtension(const std::string &filename) {
    
    size_t pos = filename.rfind('.');
    string extension = filename.substr(pos + 1);
    
    return Text::toLower(extension);
}

/**
 * Retrieves the log of a shader.
 * 
 * @param handle Handle to shader
 * @return String containing log
 */
string ShaderBuilder::findLog(GLuint handle) {
    
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
 * Determines the shader type of a file by an extension.
 * 
 * @param filename Name of a file
 * @return Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @throw std::exception if file extension not recognized
 */
GLenum ShaderBuilder::findType(const std::string &filename) {
    
    string extension = findExtension(filename);
    
    if (extension == "frag") {
        return GL_FRAGMENT_SHADER;
    } else if (extension == "vert") {
        return GL_VERTEX_SHADER;
    } else {
        throw Exception("[ShaderBuilder] Extension not recognized!");
    }
}

/**
 * Loads a file into the shader's source array and passes it to OpenGL.
 * 
 * @param handle Handle of OpenGL shader
 * @param code Code loaded from file
 */
void ShaderBuilder::load(int handle, Code &code) {
    
    int len = code.size();
    const char **source = new const char*[len];
    Code::iterator it = code.begin();
    int i = 0;
    
    // Copy to source array
    while (it != code.end()) {
        source[i] = it->text.c_str();
        ++i;
        ++it;
    }
    
    // Pass to OpenGL
    glShaderSource(handle, len, source, NULL);
}

/**
 * Reads a file into memory.
 * 
 * @param filename File to read
 * @return Code from file
 */
Code ShaderBuilder::read(const string &filename) {
    
    Preprocessor preprocessor;
    
    preprocessor.parse(filename);
    return preprocessor.getCode();
}
