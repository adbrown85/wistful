/*
 * ShaderLoader.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/shader/ShaderLoader.hpp"
using namespace std;
using namespace Ggl;

/**
 * Builds a shader from a file, guessing the type.
 * 
 * @param filename Path to a file
 * @throw std::exception if file extension not recognized
 */
GLuint ShaderLoader::load(const string &filename) {
    return load(filename, findType(filename));
}

/**
 * Builds a shader from a file using a type.
 * 
 * @param filename Path to a file
 * @param type Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @throw std::exception if type not recognized
 * @throw std::exception if file cannot be opened
 */
GLuint ShaderLoader::load(const string &filename, GLenum type) {
    
    ShaderBuilder sb;
    Code code = read(filename);
    Code::iterator it = code.begin();
    
    while (it != code.end()) {
        sb.addLine(it->text);
        ++it;
    }
    
    return sb.toShader(type);
}

//----------------------------------------
// Helpers
//

/**
 * Determines the extension of a file.
 * 
 * @param filename Name of file
 * @return Text after period converted to lowercase
 */
string ShaderLoader::findExtension(const std::string &filename) {
    
    size_t pos = filename.rfind('.');
    string extension = filename.substr(pos + 1);
    
    return Text::toLower(extension);
}

/**
 * Determines the shader type of a file by an extension.
 * 
 * @param filename Name of a file
 * @return Type of shader, e.g. GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @throw std::exception if file extension not recognized
 */
GLenum ShaderLoader::findType(const std::string &filename) {
    
    string extension = findExtension(filename);
    
    if (extension == "frag") {
        return GL_FRAGMENT_SHADER;
    } else if (extension == "vert") {
        return GL_VERTEX_SHADER;
    } else {
        throw Exception("[ShaderLoader] Extension not recognized!");
    }
}

/**
 * Reads a file into memory.
 * 
 * @param filename File to read
 * @return Code from file
 */
Code ShaderLoader::read(const string &filename) {
    
    Preprocessor preprocessor;
    
    preprocessor.parse(filename);
    return preprocessor.getCode();
}
