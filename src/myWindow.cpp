#include "headers/myWindow.h"

#include <SOIL.h>

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
    // Texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height;
    unsigned char* image = SOIL_load_image("textures/triforce.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    // Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *) (3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
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

    GLfloat timeValue = QTime().currentTime().msecsSinceStartOfDay();
    GLfloat greenValue = (GLfloat)(sin(timeValue*M_PI)/2 + 0.5f);
    GLint vertexColorLocation = glGetUniformLocation(shader->Program, "ourColor");
    glUniform4f(vertexColorLocation, greenValue, greenValue*0.6f, 0.0f, 1.0f);

    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(0.f, 0.f, 0.f));
    trans = glm::rotate(trans, (GLfloat)(QTime().currentTime().msecsSinceStartOfDay()*speed), glm::vec3(0.f, 1.f, 0.f));
    GLint transformLoc = glGetUniformLocation(shader->Program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader->Program, ""), 0);
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0,3);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
