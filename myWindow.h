#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "myGLWidget.h"

#include <QTime>

class myWindow : public myGLWidget {
Q_OBJECT
public:
    explicit myWindow(QGLFormat &format, QWidget *parent = 0);

    void initializeGL();

    void resizeGL(int width, int height);

    void paintGL();

private:
    char *name = "OpenGL";
    GLuint shaderProgram;
    GLuint VBO, VAO, EBO;
    GLint success;
    GLchar infoLog[512];

    const GLchar *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 position;\n"
            "void main()\n"
            "{\n"
            "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
            "}\0";

    const GLchar *fragmentShaderSource = "#version 330 core\n"
            "out vec4 color;\n"
            "uniform vec4 ourColor;\n"
            "void main()\n"
            "{\n"
            "color = ourColor;\n"
            "}\n\0";

    GLfloat vertices[20] = {
            -0.5f, -0.5f, 0.f,
            0.f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            -0.25f, 0.f, 0.f,
            0.25f, 0.f, 0.f,
            0.f, 0.5f, 0.f
    };
    GLuint indices[9] = {
            0,1,3,
            1,2,4,
            3,4,5
    };
};

#endif // MYWINDOW_H
