#ifndef COMMANDLINKBUTTON_H
#define COMMANDLINKBUTTON_H

#include <QCommandLinkButton>
#include <QMouseEvent>

#include<global.h>

class CommandLinkButton : public QCommandLinkButton
{
Q_OBJECT
public:
    explicit CommandLinkButton(ShaderLab::Shader shadertype, QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked(ShaderLab::Shader shaderType);

private:
    ShaderLab::Shader shaderType;
};

#endif // COMMANDLINKBUTTON_H