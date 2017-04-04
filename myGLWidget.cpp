#include "myGLWidget.h"

myGLWidget::myGLWidget(const QGLFormat &format, int framesPerSecond, QWidget *parent, char *name)
        : QGLWidget(format, parent) {
    setWindowTitle(name);
    if (framesPerSecond == 0)
        t_Timer = NULL;
    else {
        int seconde = 1000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer();
        t_Timer->setInterval(timerInterval);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start();

    }
}

void myGLWidget::keyPressEvent(QKeyEvent *keyEvent) {
    switch (keyEvent->key()) {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Space:
            if (t_Timer->isActive())
                t_Timer->stop();
            else
                t_Timer->start();
        default:
            break;
    }
}

void myGLWidget::timeOutSlot() {
    updateGL();
}
