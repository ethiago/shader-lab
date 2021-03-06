#include "objectcontroller.h"
#include "vertexproperties.h"
#include "MainWindow.h"
#include "SLObject.h"
#include "Global.h"
#include "attributeview.h"
#include "plugincontroller.h"
#include <QGLWidget>
#include "Object3D.h"
#include "slgl3w.h"

ObjectController::ObjectController(MainWindow *mw, SLObject* obj) :
    QObject(NULL), m_vertexProperties(new VertexProperties(mw)),
    e_object(obj), m_attributeView(new AttributeView),
    m_pluginController(new PluginController(mw->pluginMenu(),obj))
{
    mw->addDockWidget(Qt::RightDockWidgetArea, m_vertexProperties);
    setupPropertiesList();
    m_vertexProperties->addWidget(variantEditor);
    m_vertexProperties->addItem();
    m_vertexProperties->hide();

    m_vertexProperties->addWidget(m_attributeView);

    connect(m_vertexProperties, SIGNAL(objectChanged(int)),
            this, SIGNAL(objectChanged(int)));

    connect(m_pluginController, SIGNAL(pluginRunned()),
            this, SLOT(updateView()));

    updateView();
}

ObjectController::~ObjectController()
{
    delete m_vertexProperties;
    delete m_pluginController;
}

void ObjectController::setObject(SLObject *obj)
{
    e_object = obj;
    m_pluginController->changeObject(obj);
    updateView();
}

void ObjectController::newObject(SLObject *obj)
{
    m_vertexProperties->addItem();
    setObject(obj);
}

void ObjectController::setupPropertiesList()
{
    variantManager = new QtVariantPropertyManager();
    variantFactory = new QtVariantEditorFactory();
    variantEditor = new QtTreePropertyBrowser();
    variantEditor->setFactoryForManager(variantManager, variantFactory);
    variantEditor->setPropertiesWithoutValueMarked(true);
    variantEditor->setRootIsDecorated(false);

    topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                QLatin1String("Model Property"));
    {
        item = variantManager->addProperty(QVariant::Color,
                                           QLatin1String("Model Color"));
        item->setValue(e_object->color());
        topItem->addSubProperty(item);
        properties.insert(ModelColor, item);
    }
    {
        item = variantManager->addProperty(QVariant::Bool,
                                           QLatin1String("Visible"));
        item->setValue(e_object->isVisible());
        topItem->addSubProperty(item);
        properties.insert(Visibible, item);
    }
    variantEditor->addProperty(topItem);

    connect(variantEditor, SIGNAL(currentItemChanged(QtBrowserItem*)),
            this, SLOT(attributeChanged(QtBrowserItem*)));

    connect(variantManager, SIGNAL(valueChanged(QtProperty*,QVariant)),
            this , SLOT(valueChanged(QtProperty*,QVariant)));

}

void ObjectController::attributeChanged(QtBrowserItem* )
{
    bool v = properties.value(Visibible)->value().value<bool>();
    e_object->setVisible(v);

    QColor c = properties.value(ModelColor)->value().value<QColor>();
    e_object->setColor(c);

    ShaderLab *sl = ShaderLab::instance();
    sl->glContext()->updateGL();
}

void ObjectController::valueChanged(QtProperty*,QVariant)
{
    bool v = properties.value(Visibible)->value().value<bool>();
    e_object->setVisible(v);

    QColor c = properties.value(ModelColor)->value().value<QColor>();
    e_object->setColor(c);

    ShaderLab *sl = ShaderLab::instance();
    sl->glContext()->updateGL();
}

void ObjectController::updateView()
{
    properties.value(Visibible)->setValue(e_object->isVisible());
    properties.value(ModelColor)->setValue(e_object->color());

    m_attributeView->clear();

    const Object3D * obj = e_object->object();

    QList<PLYDataHeader::Property> infos = obj->getAttributeInfos();
    for(int i = 0; i < infos.size(); ++i)
    {
        m_attributeView->addAttribute( (QVariant::Type)infos[i].type(), infos[i].name(), infos[i].isList() );
    }

    infos = obj->getFaceUniformInfos();
    for(int i = 0; i < infos.size(); ++i)
    {
        m_attributeView->addFaceUniform((QVariant::Type)infos[i].type(), infos[i].name(), infos[i].isList() );
    }

    infos = obj->getUniformInfos();
    for(int i = 0; i < infos.size(); ++i)
    {
        m_attributeView->addUniform((QVariant::Type)infos[i].type(), infos[i].name(), infos[i].isList() );
    }
}

void ObjectController::afterLink(unsigned int programId)
{
    Object3D * obj = e_object->object();
    QList<PLYDataHeader::Property> infos = obj->getAttributeInfos();
    for(int i = 0; i < infos.size(); ++i)
    {
        int loc = SLGl3W::getAttributeLocation(programId, infos[i].name());
        obj->setAttributeLocation(i, loc);
    }

    infos = obj->getFaceUniformInfos();
    for(int i = 0; i < infos.size(); ++i)
    {
        int loc = SLGl3W::getUniformLocation(programId, infos[i].name());
        obj->setFaceUniformLocation(i, loc);
    }

    infos = obj->getUniformInfos();
    for(int i = 0; i < infos.size(); ++i)
    {
        int loc = SLGl3W::getUniformLocation(programId, infos[i].name());
        obj->setUniformLocation(i, loc);
    }

    obj->afterLink(programId);
}
