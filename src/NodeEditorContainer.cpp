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
    
}

void NodeEditorContainer::createLayouts()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    //mainLayout->addWidget();
    setLayout(mainLayout);
}