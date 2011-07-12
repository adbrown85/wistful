/*
 * ProgramBuilder.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ggl/shader/ProgramBuilder.hpp"
using namespace std;
using namespace Ggl;

/**
 * Constructs a program builder.
 */
ProgramBuilder::ProgramBuilder() {
    ;
}

/**
 * Destroys a program builder.
 */
ProgramBuilder::~ProgramBuilder() {
    ;
}

/**
 * Adds a shader to the program being built.
 * 
 * @param filename Path to a shader file to load
 * @throw std::exception if file extension not recognized
 */
void ProgramBuilder::addShader(const string &filename) {
    addShader(ShaderLoader::load(filename));
}

/**
 * Adds a shader to the program being built.
 * 
 * @param shader Existing shader to add
 */
void ProgramBuilder::addShader(GLuint shader) {
    shaders.push_back(shader);
}

/**
 * Finishes building a shader program.
 * 
 * @return Handle to the new shader program
 */
GLuint ProgramBuilder::toProgram() {
    
    GLint linked;
    GLuint handle = glCreateProgram();
    list<GLuint>::iterator it;
    
    // Attach all the shaders
    for (it=shaders.begin(); it!=shaders.end(); ++it) {
        glAttachShader(handle, (*it));
    }
    shaders.clear();
    
    // Link the program together
    glLinkProgram(handle);
    glGetProgramiv(handle, GL_LINK_STATUS, &linked);
    if (!linked) {
        report(handle);
    }
    
    return handle;
}

/**
 * Prints the log.
 * 
 * @param handle OpenGL handle to a shader program
 */
void ProgramBuilder::report(GLuint handle) {
    
    GLchar *log;
    GLint count=0, returned=0;
    
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &count);
    log = new GLchar[count+1];
    glGetProgramInfoLog(handle, count, &returned, log);
    log[returned] = '\0';
    
    cout << log << endl;
    delete[] log;
}
