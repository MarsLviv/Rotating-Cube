#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometry.h"

#include <QGLWidget>
#include <QGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QGLShaderProgram>


class Geometry;

class MainWindow : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent (QMouseEvent* e);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();

private:
    QGLShaderProgram program;
    Geometry geometries;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    QQuaternion rotation;

};

#endif // MAINWIDGET_H
