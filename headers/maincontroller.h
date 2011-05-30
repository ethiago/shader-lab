#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QMap>

#include "global.h"

class MainWindow;
class FileController;
class Object3D;

class MainController : public QObject
{
    Q_OBJECT

public:
    explicit MainController(MainWindow *mw, QObject *parent = 0);
    ~MainController();

public slots:
    void closeShaderCode(ShaderLab::Shader);
    void fileChanged(ShaderLab::Shader);
    void newShaderCode(ShaderLab::Shader);
    void openShaderCode(const QString& filename, ShaderLab::Shader);
    void programCloseRequest(void);
    void runAllActiveShaders(void);
    void saveAll(void);
    void saveFile(ShaderLab::Shader shadertype);
    void saveFileAs(ShaderLab::Shader shadertype, const QString&, const QString&);

signals:
    void updateGL(void);

private:
    MainWindow *mainWindow;
    QMap<ShaderLab::Shader, FileController*> fileControllers;

};

#endif // MAINCONTROLLER_H
