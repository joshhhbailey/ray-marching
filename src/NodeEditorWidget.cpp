#include "NodeEditorWidget.h"
#include "TestNode.h"
#include "SphereNode.h"
#include "RayMarchNode.h"

#include <QtWidgets/QVBoxLayout>

#include <iostream>

NodeEditorWidget::NodeEditorWidget(NGLScene *_scene)
{
    m_scene = _scene;
    setTitle("Node Graph");
    createWidgets();
    createLayouts();
    setupNodeGraph();
}

void NodeEditorWidget::createWidgets()
{
    m_nodeEditorScene = new QtNodes::FlowScene(registerDataModels());
    m_nodeEditorView = new QtNodes::FlowView(m_nodeEditorScene);
}

void NodeEditorWidget::createLayouts()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_nodeEditorView);
    setLayout(mainLayout);
}

void NodeEditorWidget::setupNodeGraph()
{
    m_nodeEditorScene->createNode(std::make_unique<RayMarchNode>());
}

std::shared_ptr<DataModelRegistry> NodeEditorWidget::registerDataModels()
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


void NodeEditorWidget::setStyle()
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