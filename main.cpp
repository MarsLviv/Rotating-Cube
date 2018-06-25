// ROTATING CUBE USING OpenGL/QUATERNION/SHADERS

/* project was made in Qt 5.2.0 on Ubuntu 16.4  2018.06.25
 *
 * after Qt installation were used these commands:
 * sudo apt-get install build-essential // Install g++
 * sudo apt-get install libfontconfig1  // install fonts
 * sudo apt-get install mesa-common-dev // install OpenGL libraries
 * sudo apt-get install libglu1-mesa-dev -y // sometime you need it
 * */

#include <QApplication>
#include <QLabel>

#ifndef QT_NO_OPENGL
#include "mainwindow.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Rotating cube");
#ifndef QT_NO_OPENGL
    MainWindow widget;
    widget.show();
#else
    QLabel note("You need OpenGL Support");
    note.show();
#endif
    return app.exec();
}
