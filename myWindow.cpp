#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "myWindow.h"

myWindow::myWindow(QGLFormat &format, QWidget *parent)
        : myGLWidget(format, 500, parent, (char *) "PaintGL") {
}

void myWindow::initializeGL() {
    QGLFormat glFormat = QGLWidget::format();
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();
    //Shader
    shader = new Shader("shaders/vertexShader.vs", "shaders/fragmentShader.vs");
    // Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //GLint nrAttributes;
    //glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    //std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void myWindow::resizeGL(int width, int height) {
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myWindow::paintGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->Use();

    GLfloat timeValue = QTime().currentTime().msec()*0.001f;
    GLfloat greenValue = (GLfloat)(sin(timeValue*M_PI)/2 + 0.5f);
    GLint vertexColorLocation = glGetUniformLocation(shader->Program, "ourColor");
    glUniform4f(vertexColorLocation, greenValue, greenValue*0.6f, 0.0f, 1.0f);

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0,3);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
