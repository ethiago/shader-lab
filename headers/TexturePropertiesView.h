#ifndef TEXTUREPROPERTIESVIEW_H
#define TEXTUREPROPERTIESVIEW_H

#include <QDockWidget>
#include <QList>


namespace Ui {
    class TexturePropertiesView;
}

class Texture;
class MainWindow;

class TexturePropertiesView : public QDockWidget
{
    Q_OBJECT

signals:
    void loadTextureClicked(void);
    void removeTextureClicked(void);
    void addTextureClicked(void);
    void textureCurrentChange(int);
    void addTexture3DClicked(void);

public:
    explicit TexturePropertiesView(MainWindow *parent = 0);
    ~TexturePropertiesView();

    void setTexture(const Texture& texture);

    void setTextureList(const QList<QPair<QIcon, QString> >&, int);

private:
    Ui::TexturePropertiesView *ui;
};

#endif // TEXTUREPROPERTIESVIEW_H
