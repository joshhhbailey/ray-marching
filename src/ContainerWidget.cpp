#include "ContainerWidget.h"

#include <QtWidgets/QVBoxLayout>

ContainerWidget::ContainerWidget(NGLScene *_scene)
{
    m_scene = _scene;

    createWidgets();
    createLayouts();
}

void ContainerWidget::createWidgets()
{
    m_shaderCodeWidget = new ShaderCodeWidget(m_scene);
}

void ContainerWidget::createLayouts()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_shaderCodeWidget);
    mainLayout->addStretch();
    setLayout(mainLayout);
}