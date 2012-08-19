#ifndef PRIMITIVESDIALOG_H
#define PRIMITIVESDIALOG_H

#include <GL/gl3.h>
#include <GL/glext.h>
#include <QtOpenGL>
#include <QDialog>

namespace Ui {
    class PrimitivesDialog;
}

class PrimitivesDialog : public QDialog {
    Q_OBJECT

    Ui::PrimitivesDialog *ui;

public:
    PrimitivesDialog(QWidget *parent = 0);
    ~PrimitivesDialog();

    int getCurrentOutputPrimitiveIndex(void);
    GLenum getCurrentOutputPrimitive(void);
    GLuint getOutputVertexCount(void);
    void setMaxOutputVertexOut(int);

signals:
    void valueChanged();

private:
    void primitiveSetup();


};

#endif // PRIMITIVESDIALOG_H
