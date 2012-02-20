#ifndef GLOBAL_H
#define GLOBAL_H

#include <QGLShader>
#include <QGLContext>
#include <QString>
#include <cmath>

#define QT47_CAPABLE

class ShaderLab {

    int m_extensions;

    QGLWidget *m_context;

    static ShaderLab *s_instance;
    ShaderLab();

public:

    static ShaderLab *instance()
    {
        if (!s_instance)
            s_instance = new ShaderLab;
        return s_instance;
    }

    int extensions();

    enum Shader{ Vertex, Fragment, Geometry };

    enum ExtensionSupport{ FramebufferObject = 1,
                       VertexShader = 2,
                       GeometryShader = 4,
                       FragmentShader = 8,
                       ShaderObjects = 16};

    void extensionsAnalise();
    bool criticalExtensionsEnabled();
    bool vertexShaderEnabled();
    bool fragmentShaderEnabled();
    bool geometryShaderEnabled();
    void setContext(QGLWidget*);
    QGLWidget* glContext();


    static QString shaderToStrCap(Shader s);
    static QString shaderToStr(Shader s);
    static QString shaderToExt(Shader s);

    static QGLShader::ShaderTypeBit shaderToQGLShader(Shader s);

    static int shaderToInt(Shader s);
    static Shader intToShader(int v);

    static double degreeFromCos(double);

    static QList<ShaderLab::Shader> shaderTypeList(void);
    static QList<ShaderLab::Shader> enabledsShaderTypeList(void);
};

#define FORSHADERS(varname) foreach(ShaderLab::Shader varname, ShaderLab::shaderTypeList())
#define FORENABLEDSHADERS(varname) foreach(ShaderLab::Shader varname, ShaderLab::enabledsShaderTypeList())


#endif // GLOBAL_H
