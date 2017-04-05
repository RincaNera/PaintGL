#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "myGLWidget.h"
#include "Shader.h"

#include <QTime>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class myWindow : public myGLWidget {
Q_OBJECT
public:
    explicit myWindow(QGLFormat &format, QWidget *parent = 0);

    void initializeGL();

    void resizeGL(int width, int height);

    void paintGL();

private:
    GLuint VBO, VAO, EBO, texture;
    Shader *shader = NULL;
    GLfloat speed = 0.005f;

    GLfloat vertices[32] = {
            -0.5f, -0.5f, 0.f,  0.f, 0.f,   // Bottom left
            0.f, -0.5f, 0.f,    0.5f, 0.f,  // Bottom
            0.5f, -0.5f, 0.f,   1.f, 0.f,   // Bottom Right
            -0.25f, 0.f, 0.f,   0.f, 0.5f,  // Left
            0.25f, 0.f, 0.f,    1.f, 0.5f,  // Right
            0.f, 0.5f, 0.f,     0.5f, 1.f   // Top
    };
    GLuint indices[9] = {
            0,1,3,
            1,2,4,
            3,4,5
    };
    GLfloat texCoords[6] = {
            0.0f, 0.0f,  // Lower-left corner
            1.0f, 0.0f,  // Lower-right corner
            0.5f, 1.0f   // Top-center corner
    };
};

#endif // MYWINDOW_H
