#include "mainwindow.h"

#include <QMouseEvent>

#include <math.h>
#include <locale.h>

MainWindow::MainWindow(QWidget *parent) :
    QGLWidget(parent){
}

MainWindow::~MainWindow(){
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    mousePressPosition = QVector2D(e->localPos());
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    // Current mouse position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse trajectory
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Rotation angle relative to the length of the mouse sweep
    qreal angle = diff.length() / 40;

    // New rotation axis
    rotationAxis = n.normalized();

    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
    updateGL();
}

void MainWindow::initializeGL()
{
    initializeGLFunctions();
    qglClearColor(Qt::lightGray);
    glShadeModel(GL_FLAT);// not works ???
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    //glEnable(GL_CULL_FACE);

    geometries.init();
}

void MainWindow::initShaders()
{
    // Override system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");
}

void MainWindow::resizeGL(int w, int h){
    glViewport(0, 0, w, h);

    // aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWindow::paintGL(){
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Send modelview-projection matrix to shader using "mvp_matrix"
    program.setUniformValue("mvp_matrix", projection * matrix);

    // Draw cube geometry
    geometries.drawGeometry(&program);
}
