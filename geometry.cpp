#include "geometry.h"

Geometry::Geometry(){
}

Geometry::~Geometry(){
    glDeleteBuffers(2, vboIds);
}

void Geometry::init()
{
    initializeGLFunctions();

    // Generate 2 VBOs
    glGenBuffers(2, vboIds);

    // Initializes geometry and transfers it to VBOs
    initGeometry();
}

void Geometry::initGeometry()
{   //const GLubyte* pVersion = glGetString(GL_VERSION);
    //qDebug() << "Version: " << *pVersion;
    GLfloat vertices[] = {
        -1.0, -1.0,  1.0, 1.0f, 0.0f, 0.0f , // v0 front face - red
         1.0, -1.0,  1.0, 1.0f, 0.0f, 0.0f , // v1
        -1.0,  1.0,  1.0, 1.0f, 0.0f, 0.0f , // v2
         1.0,  1.0,  1.0, 1.0f, 0.0f, 0.0f , // v3

         1.0, -1.0, -1.0, 0.0f, 0.0f, 1.0f, //  v4 back face - blue
        -1.0, -1.0, -1.0, 0.0f, 0.0f, 1.0f,  // v5
         1.0,  1.0, -1.0, 0.0f, 0.0f, 1.0f, //  v6
        -1.0,  1.0, -1.0, 0.0f, 0.0f, 1.0f, //  v7

         1.0, -1.0,  1.0, 0.0f, 1.0f, 0.0f , // v8 (1 again) right face - green
         1.0, -1.0, -1.0, 0.0f, 1.0f, 0.0f, //  v9 (4 again)
         1.0,  1.0, -1.0, 0.0f, 1.0f, 0.0f, //  v10 (6 again)
         1.0,  1.0,  1.0, 0.0f, 1.0f, 0.0f, //  v11 (3 again)

        -1.0, -1.0,  1.0, 1.0f, 1.0f, 0.0f , // v12 (0 again) left face - yellow
        -1.0,  1.0,  1.0, 1.0f, 1.0f, 0.0f , // v13 (2 again)
        -1.0,  1.0, -1.0, 1.0f, 1.0f, 0.0f, //  v14 (7 again)
        -1.0, -1.0, -1.0, 1.0f, 1.0f, 0.0f,  // v15 (5 again)

        -1.0,  1.0,  1.0, 1.0f, 0.0f, 1.0f , // v16 (2 again) top face - magenta
         1.0,  1.0,  1.0, 1.0f, 0.0f, 1.0f , // v17 (3 again)
         1.0,  1.0, -1.0, 1.0f, 0.0f, 1.0f, //  v18 (6 again)
        -1.0,  1.0, -1.0, 1.0f, 0.0f, 1.0f, //  v19 (7 again)

        -1.0, -1.0,  1.0, 0.0f, 1.0f, 1.0f , // v20 (0 again) bottom face - cyan
         1.0, -1.0,  1.0, 0.0f, 1.0f, 1.0f , // v21 (1 again)
         1.0, -1.0, -1.0, 0.0f, 1.0f, 1.0f, //  v22 (4 again)
        -1.0, -1.0, -1.0, 0.0f, 1.0f, 1.0f  // v23 (5 again)
    };
    GLushort indices[] = {
        0, 1, 3, 2   // front face
        , 4, 5, 7, 6 // back face
        , 8, 9, 10, 11// right face
        ,12, 13, 14, 15// left face
        ,16, 17, 18, 19// top face
        ,20, 21, 22, 23// bottom face
    };

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 6*24 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*4 * sizeof(GLushort), indices, GL_STATIC_DRAW);
}

void Geometry::drawGeometry(QGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");// get pointer to DATA "a_position"
    program->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)offset);

    // Offset for vertex coordinate
    offset += sizeof(GLfloat) * 3;

    // Tell OpenGL programmable pipeline how to locate vertex color data
    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)offset);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_QUADS, 6*4, GL_UNSIGNED_SHORT, 0);
}

