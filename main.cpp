#include <iostream>

#include <QApplication>

#include "myWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QGLFormat glFormat;
    glFormat.setVersion(3, 3);
    glFormat.setProfile(QGLFormat::CoreProfile); // Requires >=Qt-4.8.0
    glFormat.setSampleBuffers(true);
    myWindow myWin(glFormat); //Ajout de notre classe myWindow
    myWin.show();   //Exécution de notre fenêtre de rendu OpenGL
    return app.exec();
}

