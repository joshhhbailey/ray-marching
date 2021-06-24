#include "ContainerWidget.h"

#include <QtWidgets/QVBoxLayout>

ContainerWidget::ContainerWidget()
{
    createWidgets();
    createLayouts();
}

void ContainerWidget::createWidgets()
{
    m_shaderCodeWidget = new ShaderCodeWidget();
}

void ContainerWidget::createLayouts()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_shaderCodeWidget);
    mainLayout->addStretch();
    setLayout(mainLayout);
}