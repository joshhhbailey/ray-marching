#include "MaterialNodeWidget.h"

#include <QtWidgets/QFormLayout>

#include <ngl/Vec3.h>

MaterialNodeWidget::MaterialNodeWidget()
{
    createWidgets();
    createLayouts();
}

void MaterialNodeWidget::createWidgets()
{
    m_colourWidget = new Vec3Widget("Colour:", ngl::Vec3(0.0, 0.0, 0.0));
    m_colourWidget->m_xField->setRange(0.0, 1.0);
    m_colourWidget->m_yField->setRange(0.0, 1.0);
    m_colourWidget->m_zField->setRange(0.0, 1.0);
    m_colourWidget->m_xField->setSingleStep(0.01);
    m_colourWidget->m_yField->setSingleStep(0.01);
    m_colourWidget->m_zField->setSingleStep(0.01);
}

void MaterialNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow(m_colourWidget);
    setLayout(mainLayout);
}