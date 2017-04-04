#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "myGLWidget.h"
#include "Shader.h"

#include <QTime>

class myWindow : public myGLWidget {
Q_OBJECT
public:
    explicit myWindow(QGLFormat &format, QWidget *parent = 0);

    void initializeGL();

    void resizeGL(int width, int height);

    void paintGL();

private:
    GLuint VBO, VAO, EBO;
    Shader *shader = NULL;

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
