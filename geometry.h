#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QGLFunctions>
#include <QGLShaderProgram>

class Geometry : protected QGLFunctions
{
public:
    Geometry();
    virtual ~Geometry();

    void init();
    void drawGeometry(QGLShaderProgram *program);

private:
    void initGeometry();

    GLuint vboIds[2];
};

#endif // GEOMETRY_H
