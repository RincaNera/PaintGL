#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <GL/glew.h>
#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>

class myGLWidget : public QGLWidget {
Q_OBJECT
public:
    myGLWidget(const QGLFormat &format, int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);

    virtual void initializeGL() = 0;

    virtual void resizeGL(int width, int height) = 0;

    virtual void paintGL() = 0;

    virtual void keyPressEvent(QKeyEvent *keyEvent);

public slots:

    virtual void timeOutSlot();

private:
    QTimer *t_Timer;

};


#endif // MYGLWIDGET_H
