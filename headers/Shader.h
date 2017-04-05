//
// Created by rinca on 04/04/17.
//

#ifndef TUTO_OPENGL_SHADER_H
#define TUTO_OPENGL_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader {
public:
    // The Program ID
    GLuint Program;

    // Constructor reads and builds the shader
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

    // Use the program
    void Use();
};


#endif //TUTO_OPENGL_SHADER_H
