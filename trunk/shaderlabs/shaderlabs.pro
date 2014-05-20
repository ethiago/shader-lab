# -------------------------------------------------
# Project created by QtCreator 2011-03-26T13:25:06
# -------------------------------------------------
QT += core \
    gui \
    opengl \
    xml
win32 { 
    TARGET = ../ShaderLab-win32
    LIBS += -lfreeglut -lopengl32
}

unix {
    TARGET = ShaderLab-unix32
    LIBS += -lGLU -ldl    #does't work on Mac
}
#MAC
#LIBS += -framework Carbon
#/MAC

TEMPLATE = app
DEPENDPATH += ../src
INCLUDEPATH += ../headers
OBJECTS_DIR = tmp
MOC_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp
DEPLOYDIR = ../../ShaderLabs
DESTDIR = $$DEPLOYDIR/bin

#QtSolutions_PropertyBrowser-head
include(../3rd-party/qtpropertybrowser/src/qtpropertybrowser.pri)
#QtSolutions_PropertyBrowser-head

QMAKE_LFLAGS = '-Wl,-rpath,\'\$$ORIGIN/../lib\''

SLSRC=../src
SLHED=../headers
SLFOR=../forms
SLRES=../qresources

SOURCES += $$SLSRC/gl3w.c \
    $$SLSRC/main.cpp \
    $$SLSRC/Sphere.cpp \
    $$SLSRC/SLTabWidget.cpp \
    $$SLSRC/SLTabBar.cpp \
    $$SLSRC/Arcball.cpp \
    $$SLSRC/ChooseShaderDialog.cpp \
    $$SLSRC/SLCommandLinkButton.cpp \
    $$SLSRC/GLDisplay.cpp \
    $$SLSRC/Global.cpp \
    $$SLSRC/Texture.cpp \
    $$SLSRC/TexturePropertiesView.cpp \
    $$SLSRC/Plane.cpp \
    $$SLSRC/MainController.cpp \
    $$SLSRC/MainWindow.cpp \
    $$SLSRC/Object3D.cpp \
    $$SLSRC/InterfaceRequests.cpp \
    $$SLSRC/Find.cpp \
    $$SLSRC/HighLighter.cpp \
    $$SLSRC/PrimitivesDialog.cpp \
    $$SLSRC/DirectionalLight.cpp \
    $$SLSRC/Project.cpp \
    $$SLSRC/Cube.cpp \
    $$SLSRC/GlobalProperties.cpp \
    $$SLSRC/Tetrahedron.cpp \
    $$SLSRC/Point.cpp \
    $$SLSRC/Scene3D.cpp \
    $$SLSRC/SLFile.cpp \
    $$SLSRC/codeeditor.cpp \
    $$SLSRC/TrianglePatch.cpp \
    $$SLSRC/IcosahedronPatch.cpp \
    $$SLSRC/Patch.cpp \
    $$SLSRC/slgl3w.cpp \
    $$SLSRC/squarepatch.cpp \
    $$SLSRC/slShader.cpp \
    $$SLSRC/slshadercontroller.cpp \
    $$SLSRC/SLObject.cpp \
    $$SLSRC/slShaderProgram2.cpp \
    $$SLSRC/slShaderCodes.cpp \
    $$SLSRC/slCodeContainer2.cpp \
    $$SLSRC/rendercontroller2.cpp \
    $$SLSRC/slTexture2.cpp \
    $$SLSRC/slTextureController.cpp \
    $$SLSRC/slProjectController.cpp \
    $$SLSRC/vertexproperties.cpp \
    $$SLSRC/objectcontroller.cpp

HEADERS += $$SLHED/gl3w.h \
    $$SLHED/glcorearb.h \
    $$SLHED/Sphere.h \
    $$SLHED/SLTabWidget.h \
    $$SLHED/SLTabBar.h \
    $$SLHED/Arcball.h \
    $$SLHED/ChooseShaderDialog.h \
    $$SLHED/SLCommandLinkButton.h \
    $$SLHED/GLDisplay.h \
    $$SLHED/Global.h \
    $$SLHED/Texture.h \
    $$SLHED/TexturePropertiesView.h \
    $$SLHED/Plane.h \
    $$SLHED/MainController.h \
    $$SLHED/MainWindow.h \
    $$SLHED/Object3D.h \
    $$SLHED/InterfaceRequests.h \
    $$SLHED/Find.h \
    $$SLHED/HighLighter.h \
    $$SLHED/PrimitivesDialog.h \
    $$SLHED/DirectionalLight.h \
    $$SLHED/Project.h \
    $$SLHED/Cube.h \
    $$SLHED/GlobalProperties.h \
    $$SLHED/Tetrahedron.h \
    $$SLHED/Point.h \
    $$SLHED/Scene3D.h \
    $$SLHED/SLFile.h \
    $$SLHED/codeeditor.h \
    $$SLHED/TrianglePatch.h \
    $$SLHED/IcosahedronPatch.h \
    $$SLHED/Patch.h \
    $$SLHED/slgl3w.h \
    $$SLHED/squarepatch.h \
    $$SLHED/slShader.h \
    $$SLHED/slshadercontroller.h \
    $$SLHED/SLObject.h \
    $$SLHED/slShaderProgram2.h \
    $$SLHED/slShaderCodes.h \
    $$SLHED/slCodeContainer2.h \
    $$SLHED/rendercontroller2.h \
    $$SLHED/slTexture2.h \
    $$SLHED/slTextureController.h \
    $$SLHED/slProjectController.h \
    $$SLHED/vertexproperties.h \
    $$SLHED/objectcontroller.h


FORMS += $$SLFOR/MainWindow.ui \
    $$SLFOR/ChooseShaderDialog.ui \
    $$SLFOR/TexturePropertiesView.ui \
    $$SLFOR/Find.ui \
    $$SLFOR/PrimitivesDialog.ui \
    $$SLFOR/GlobalProperties.ui \
    $$SLFOR/ShaderCodeContainer2.ui
    
RESOURCES += $$SLRES/shaderlab.qrc
OTHER_FILES += 
