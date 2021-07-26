#include "NodeEditorContainer.h"
#include "TestNode.h"
#include "SphereNode.h"
#include "RayMarchNode.h"

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
    std::shared_ptr<DataModelRegistry> dataModels = std::make_shared<DataModelRegistry>();
    
    dataModels->registerModel<TestNode>("Tests");
    dataModels->registerModel<SphereNode>("SDFs");
    dataModels->registerModel<RayMarchNode>("RayMarching");

    /*dataModels->registerModel<Union>("Boolean Operators");
    dataModels->registerModel<Intersection>("Boolean Operators");
    dataModels->registerModel<Difference>("Boolean Operators");*/

  return dataModels;
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

void NodeEditorContainer::openFile()
{
  m_nodeEditorScene->load();
}

void NodeEditorContainer::saveFile()
{
  std::cout << "Save file not yet implemented.\n";
}

void NodeEditorContainer::saveAsFile()
{
  m_nodeEditorScene->save();
}