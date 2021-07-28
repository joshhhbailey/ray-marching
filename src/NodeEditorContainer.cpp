#include "NodeEditorContainer.h"

#include <QtWidgets/QVBoxLayout>

#include <iostream>

NodeEditorContainer::NodeEditorContainer(NGLScene *_scene)
{
    m_scene = _scene;
    createWidgets();
    createLayouts();
}

void NodeEditorContainer::createWidgets()
{
    m_nodeEditorWidget = new NodeEditorWidget(m_scene);
}

void NodeEditorContainer::createLayouts()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_nodeEditorWidget);
    setLayout(mainLayout);
}

void NodeEditorContainer::newFile()
{
  m_nodeEditorWidget->getNodeEditorScene()->clearScene();
  m_nodeEditorWidget->setupNodeGraph();
}

void NodeEditorContainer::openFile()
{
  m_nodeEditorWidget->getNodeEditorScene()->load();
}

void NodeEditorContainer::saveFile()
{
  std::cout << "Save file not yet implemented.\n";
}

void NodeEditorContainer::saveAsFile()
{
  m_nodeEditorWidget->getNodeEditorScene()->save();
}