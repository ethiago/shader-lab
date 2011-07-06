#include <QtGui/QApplication>

#include "maincontroller.h"
#include "rendercontroller.h"
#include "TextureController.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mw;
    MainController mc(&mw);
    RenderController rc(&mw, &mc);
    TextureController tc(&mw, rc.getGLContext(), &mc);

    mc.setTextureController(&tc);

    QObject::connect(&mc, SIGNAL(updateGL()), &rc, SLOT(updateGL()));
    QObject::connect(&tc, SIGNAL(updateTexture(int)), &rc,SLOT(updateTexture(int)));

    return a.exec();
}