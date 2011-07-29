#include <QFile>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSize>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GLDisplay.h"
#include "SLTabWidget.h"
#include "SLTabBar.h"


/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* +++++++++++++++++ Constructors and destructors ++++++++++++++++++ */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabArea = new SLTabWidget();
    tabArea->setTabsClosable(true);
    tabArea->setMovable(true);

    ui->dockOutPutWidget->setVisible(true);
    ui->actionShowOutput->setChecked(true);

    connect(ui->actionOpenCode, SIGNAL(triggered()),
            this, SLOT(openDialog()));

    connect(ui->actionNewFile, SIGNAL(triggered()),
            this, SLOT(newDialog()));

    connect(tabArea, SIGNAL(tabCloseRequested(int)),
            this, SLOT(closeTabRequest(int)));

    connect(ui->actionExit, SIGNAL(triggered()),
            this, SLOT(exitApplication()));

    connect(ui->actionRunAll, SIGNAL(triggered()),
            this, SLOT(runSelectedShaders()));

    connect(ui->menuView, SIGNAL(triggered(QAction*)),
            this, SLOT(viewMenuClicked(QAction*)));

    connect(ui->dockOutPutWidget, SIGNAL(visibilityChanged(bool)),
            this, SLOT(dockOutputVisibilityChange(bool)));

    connect(ui->dockRenderWidget, SIGNAL(visibilityChanged(bool)),
            this, SLOT(dockRenderVisibilityChange(bool)));

    connect(ui->actionSaveFile, SIGNAL(triggered()),
            this, SLOT(saveFile()));

    connect(ui->actionSaveAs, SIGNAL(triggered()),
            this, SLOT(saveFileAsDialog()));

    connect(ui->actionSaveAll, SIGNAL(triggered()),
            this, SIGNAL(saveAll()));

    connect(ui->actionWireframe, SIGNAL(toggled(bool)),
            this, SIGNAL(wireframeClicked(bool)));

    connect(tabArea->getTabBar(), SIGNAL(signal_TabClicked()),
            this, SLOT(changeActivationStatus()));

    connect(ui->actionSave_Result_as_Image, SIGNAL(triggered()),
            this, SIGNAL(saveResultAsImage()));

    connect(ui->actionNewFile, SIGNAL(triggered()),
            this, SIGNAL(newShaderActionClicked()));

    connect(ui->actionOpenCode, SIGNAL(triggered()),
            this, SIGNAL(openShaderActionClicked()));

}

MainWindow::~MainWindow()
{
    QMap<ShaderLab::Shader, ShaderCodeContainer*>::iterator it;
    ShaderCodeContainer* pt;
    for(it = codeTabs.begin(); it != codeTabs.end(); ++it)
    {
        pt = it.value();
        delete pt;
    }

    delete ui;
    delete tabArea;
}


/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* ++++++++++++++++++++++ Getters and setters ++++++++++++++++++++++ */

/* Setter for the output text on the screen. */
bool MainWindow::setOutputText(const QString& s)
{
    ui->outputTextBox->clear();
    ui->outputTextBox->setPlainText(s);

    return true;
}

/* Getter for the output text on the screen. */
QString MainWindow::getOutputText(void)
{
    return ui->outputTextBox->toPlainText();
}

/* Sets the name displayed for a file, depending if the content has changed. */
/* (Displays a '*' when it is.) */
void MainWindow::setFileNameDisplay(QString filename, bool changed, ShaderLab::Shader shadertype)
{
    QMap<ShaderLab::Shader, ShaderCodeContainer *>::iterator it;
    it = codeTabs.find(shadertype);

    QString display = (changed ? QString("*") : QString()) + filename;

    if(it != codeTabs.end())
    {
        int ind = tabArea->indexOf(it.value());

        if(ind != -1)
        {
            tabArea->setTabText(ind, display);
        }
    }
}

/* Given the content, displays it on the apropriate tab. */
bool MainWindow::setShaderCode(const QString& code, ShaderLab::Shader shadertype)
{
    QMap<ShaderLab::Shader, ShaderCodeContainer *>::iterator it;

    it = codeTabs.find(shadertype);

    if(it != codeTabs.end())
    {
        it.value()->setText(code);
        return true;
    }
    else return false;
}

/* Displays or removes the desired tab from the screen. */
bool MainWindow::setVisibleShader(bool v, ShaderLab::Shader shadertype)
{
    QMap<ShaderLab::Shader, ShaderCodeContainer *>::iterator it;
    it = codeTabs.find(shadertype);

    if(it == codeTabs.end())
        return false;

    int ind = tabArea->indexOf(it.value());

    if(v == true)
    {
        if(tabArea->count() == 0)
        {
            tabArea->setParent(ui->centralWidget);
            ui->horizontalLayout->addWidget(tabArea);
        }
        if(ind == -1)
        {
            tabArea->insertTab(tabArea->count(), it.value(), QString());
            tabArea->setCurrentIndex(tabArea->count() -1);
            tabArea->setTabIcon(tabArea->count() - 1, QIcon(":/ico/running"));
        }
    }
    else
    {
        if(ind != -1)
            tabArea->removeTab(ind);
        if(tabArea->count() == 0)
        {
            ui->horizontalLayout->removeWidget(tabArea);
            tabArea->setParent(0);
        }
    }

    return true;
}


/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* +++++++++++++++++++++++++++++ Slots +++++++++++++++++++++++++++++ */

/* Associated with the 'tabCloseRequested' signal, from QTabWidget. */
/* Encapsulates the signal comming from the UI and passes itto the MainController, as a 'closeTabRequest' signal. */
void MainWindow::closeTabRequest(int index)
{
    ShaderCodeContainer *pt = (ShaderCodeContainer*)tabArea->widget(index);
    emit closeTabRequest(pt->getShaderType());
}

/* Associated with the '' signal. */
/* */
void MainWindow::dockOutputVisibilityChange(bool v)
{
    ui->actionShowOutput->setChecked(v);
}

/* Associated with the '' signal. */
/* */
void MainWindow::dockRenderVisibilityChange(bool v)
{
    ui->actionShowRenderArea->setChecked(v);
}

/* Associated with the '' signal. */
/* */
void MainWindow::exitApplication(void)
{
    close(); //closeEvent
}

/* Associated with the '' signal. */
/* */
void MainWindow::runSelectedShaders(void)
{
    emit runShaders();
}

/* Associated with the '' signal. */
/* */
void MainWindow::saveFile(void)
{
    ShaderCodeContainer* shaderTab = ((ShaderCodeContainer*)tabArea->currentWidget());
    if(shaderTab != NULL)
    {
        ShaderLab::Shader shadertype = shaderTab->getShaderType();
        emit saveFile(shadertype);
    }
}

/* Associated with the '' signal. */
/* */
void MainWindow::saveFileAsDialog(void)
{
    ShaderCodeContainer* shaderTab = ((ShaderCodeContainer*)tabArea->currentWidget());
    if(shaderTab != NULL)
    {
        ShaderLab::Shader shadertype = shaderTab->getShaderType();

        emit saveFileAs(shadertype);
    }
}

/* Associated with the '' signal. */
/* */
void MainWindow::selectedShaderNewDialog(ShaderLab::Shader shadertype)
{
    emit newShaderFile(shadertype);
}

/* Associated with the '' signal. */
/* */
void MainWindow::selectedShaderOpenDialog(ShaderLab::Shader sh)
{
    emit selectedFile(sh);
}

/* Associated with the '' signal. */
/* */
void MainWindow::textChanged(ShaderLab::Shader shadertype)
{
    emit shaderCodeChanged(shadertype);
}

/* Associated with the '' signal. */
/* */
void MainWindow::viewMenuClicked(QAction* act)
{
    if(act == ui->actionShowOutput)
        ui->dockOutPutWidget->setVisible(act->isChecked());
    else if(act == ui->actionShowRenderArea)
        ui->dockRenderWidget->setVisible(act->isChecked());

}


/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* +++++++++++++++++++++++++ Other methods +++++++++++++++++++++++++ */

/* */
void MainWindow::addShader(ShaderLab::Shader shadertype)
{
    ShaderCodeContainer *codeContainer = new ShaderCodeContainer(shadertype);
    codeTabs.insert(shadertype, codeContainer);

    connect(codeContainer, SIGNAL(textChanged(ShaderLab::Shader)),
            this, SLOT(textChanged(ShaderLab::Shader)));
    connect(codeContainer, SIGNAL(doubleClicked()),
            this, SLOT(changeActivationStatus()));

}

/* */
void MainWindow::closeEvent(QCloseEvent *event)
{
    emit programClose(event);
}

/* */
QString MainWindow::shaderCode(ShaderLab::Shader shadertype)
{
    QMap<ShaderLab::Shader, ShaderCodeContainer *>::iterator it;
    it = codeTabs.find(shadertype);

    if(it != codeTabs.end())
        return it.value()->getText();

    return QString();
}

/* */
bool MainWindow::visibleShader(ShaderLab::Shader shader)
{
    QMap<ShaderLab::Shader, ShaderCodeContainer *>::iterator it;
    it = codeTabs.find(shader);

    if(it != codeTabs.end())
    {
        int ind = tabArea->indexOf(it.value());
        if(ind == -1)
            return false;
        else
            return true;
    }
    else
        return false;
}

void MainWindow::setGLDisplay(GLDisplay * display)
{
    ui->verticalLayout->addWidget(display);
}

void MainWindow::setEnableShaderCode(ShaderLab::Shader shadertype, bool active)
{
    QMap<ShaderLab::Shader, ShaderCodeContainer *>::iterator it;
    it = codeTabs.find(shadertype);
    if(it == codeTabs.end())
        return;

    ShaderCodeContainer * sc = it.value();

    int ind = tabArea->indexOf(sc);

    if(ind != -1)
    {
        sc->setActivatedCode(active);
        if(active)
            tabArea->setTabIcon(ind, QIcon(":/ico/running"));
        else
            tabArea->setTabIcon(ind, QIcon(":/ico/stopped"));
    }


}

void MainWindow::changeActivationStatus(void)
{
    ShaderCodeContainer *scc = (ShaderCodeContainer*) tabArea->currentWidget();

    if(scc != NULL)
        emit changeActivationStatusClicked(scc->getShaderType());
}

QAction* MainWindow::actionTexturePropertiesView(void)
{
    return ui->actionTexture_Properties;
}

 QMenu* MainWindow::modelsMenu(void)
 {
    return ui->menu_Models;
 }
