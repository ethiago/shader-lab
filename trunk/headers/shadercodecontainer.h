#ifndef SHADERCODECONTAINER_H
#define SHADERCODECONTAINER_H

#include <QWidget>
#include <QTimer>
#include "Global.h"

namespace Ui {
    class ShaderCodeContainer;
}

class ShaderCodeContainer : public QWidget
{
    Q_OBJECT

public:
    explicit ShaderCodeContainer(ShaderLab::Shader shadertype, QWidget *parent = 0);
    ~ShaderCodeContainer();
    void setText(const QString&);
    QString getText(void);
    ShaderLab::Shader getShaderType(void);
    void setActivatedCode(bool);

private:
    Ui::ShaderCodeContainer *ui;
    QPalette activePalette;
    QPalette inactivePalette;
    ShaderLab::Shader shaderType;

private slots:
    void textChanged(void);
    void timeout(void);

signals:
    void textChanged(ShaderLab::Shader);
    void clicked(Qt::MouseButton, ShaderLab::Shader);
    void doubleClicked();

protected:
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

};

#endif // SHADERCODECONTAINER_H
