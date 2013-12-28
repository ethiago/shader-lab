#include "SLObject2.h"
#include "Project.h"
#include "InterfaceRequests.h"
#include "MainWindow.h"
#include "Object3D.h"
#include "SLShaderProgram.h"
#include "SLTextures.h"
#include "QGLWidget"

SLObject2::SLObject2(MainWindow *mw,  SLShaderProgram* slp, SLTextures* slt, QObject *parent) :
    QObject(parent), mainwindow(mw), m_shader(slp), m_object(NULL), m_textures(slt), m_project(NULL)
{
    connect(mainwindow, SIGNAL(runShaders()), this, SLOT(compileShaders()));
    connect(this, SIGNAL(sendLog(QString)), mainwindow, SLOT(shaderLog(QString)));
}

SLObject2::~SLObject2()
{
    if(m_project)
        delete m_project;
    if(m_object)
        delete m_object;
}

void SLObject2::setObject(Object3D *obj)
{
    if(m_object)
        delete m_object;
    m_object = obj;
    m_shader->setGeometryInputType(obj->inputType());
}

void SLObject2::draw()
{
    if(m_shader->isLinked())
    {
        m_shader->bind();

        m_textures->setUniformTexture(m_shader);
    }

    m_object->draw();
    m_shader->release();

}

void SLObject2::compileShaders()
{
   m_textures->activeTextures();
   m_shader->compileAndLink();
   m_textures->setupUniformTextureNames(m_shader);
   emit sendLog(m_shader->log());
   ShaderLab::instance()->glContext()->updateGL();
}

QString SLObject2::shaderLog()
{
    return m_shader->log();
}

void SLObject2::setTexturesFromProject(const QStringList& list)
{
   m_textures->setTextures(list);
}

void SLObject2::closeProject()
{
    if(m_project)
        delete m_project;
    m_project = NULL;
}

void SLObject2::setProject(Project *p)
{
    if(m_project)
        delete m_project;
    m_project = p;
}

void SLObject2::close()
{
    saveMerge(false);
    m_shader->setStandBy();

    disconnect(this, 0, mainwindow, 0);
    disconnect(mainwindow, 0, this, 0);
}

QString SLObject2::saveMerge(bool as)
{
    QString projectFileName;
    if(as)
    {
        closeProject();
    }else
    {
        if(m_project == NULL)
        {
            if(InterfaceRequests::createProject())
                as = true;
            else
                return QString();
        }
    }
    m_shader->saveAllShaders();
    if(m_shader->isAnyNew())
    {
        if(!InterfaceRequests::projectSaveContinue())
            return QString();
    }

    if(as)
    {
       projectFileName = InterfaceRequests::saveProjectAsRequestDialog();
       if(projectFileName.isEmpty())
           return QString();

        m_project = new Project;
    }
    else
        projectFileName = QString();


    FORENABLEDSHADERS(shaderType)
    {
        QString filepath = m_shader->getAbsoluteFilePath(shaderType);
        m_project->checkShader(filepath, shaderType);
    }

    m_project->setModel(m_object->modelId());
    m_project->setTextures(m_textures->getTextureFileNames());

    m_project->save(projectFileName);

    return m_project->getAbsoluteFilePath();
}

SLTextures * SLObject2::textures()
{
    return m_textures;
}

void SLObject2::toggleWireframe()
{
    m_object->setWireframe(!m_object->wireframe());
}

Object3D * SLObject2::object3D()
{
    return m_object;
}

int SLObject2::programId()
{
    return m_shader->getProgramId();
}