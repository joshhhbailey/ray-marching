#include "NodeEditorContainer.h"

#include <QtWidgets/QVBoxLayout>

#include <iostream>

NodeEditorContainer::NodeEditorContainer()
{
    createWidgets();
    createLayouts();
}

void NodeEditorContainer::createWidgets()
{
    m_nodeEditorScene = new QtNodes::FlowScene(registerDataModels());
    m_nodeEditorView = new QtNodes::FlowView(m_nodeEditorScene);
}

void NodeEditorContainer::createLayouts()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_nodeEditorView);
    setLayout(mainLayout);
}

std::shared_ptr<DataModelRegistry> NodeEditorContainer::registerDataModels()
{
    auto ret = std::make_shared<DataModelRegistry>();

/*
    //ret->registerModel<NaiveDataModel>();
    We could have more models registered.
    All of them become items in the context meny of the scene.

    ret->registerModel<AnotherDataModel>();
    ret->registerModel<OneMoreDataModel>();
*/

  return ret;
}


void NodeEditorContainer::setStyle()
{
  ConnectionStyle::setConnectionStyle(
    R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");
}