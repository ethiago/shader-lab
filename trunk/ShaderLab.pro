# -------------------------------------------------
# Project created by QtCreator 2011-03-26T13:25:06
# -------------------------------------------------
QT += core \
    gui \
    opengl

win32 {
     TARGET = ShaderLab-win32
 }
 unix {
     TARGET = ShaderLab
 }

TEMPLATE = app
DEPENDPATH += src
INCLUDEPATH += headers
OBJECTS_DIR = tmp
MOC_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp
DESTDIR = bin

SOURCES += src/main.cpp \
    src/shadercodecontainer.cpp \
    src/object3d.cpp \
    src/sphere.cpp \
    src/rendercontroller.cpp \
    src/sltabwidget.cpp \
    src/SLTabBar.cpp \
    src/Arcball.cpp \
    src/ChooseShaderDialog.cpp \
    src/SLCommandLinkButton.cpp \
    src/FileController.cpp \
    src/GLDisplay.cpp \
    src/Global.cpp \
    src/TextureController.cpp \
    src/Texture.cpp \
    src/TexturePropertiesView.cpp \
    src/Plane.cpp \
    src/MainController.cpp \
    src/MainWindow.cpp
HEADERS += \
    headers/shadercodecontainer.h \
    headers/object3d.h \
    headers/sphere.h \
    headers/rendercontroller.h \
    headers/sltabwidget.h \
    headers/SLTabBar.h \
    headers/Arcball.h \
    headers/ChooseShaderDialog.h \
    headers/SLCommandLinkButton.h \
    headers/FileController.h \
    headers/GLDisplay.h \
    headers/Global.h \
    headers/TextureController.h \
    headers/Texture.h \
    headers/TexturePropertiesView.h \
    headers/Plane.h \
    headers/MainController.h \
    headers/MainWindow.h
FORMS += forms/mainwindow.ui \
    forms/shadercodecontainer.ui \
    forms/ChooseShaderDialog.ui \
    forms/TexturePropertiesView.ui
RESOURCES += shaderlab.qrc

OTHER_FILES +=
