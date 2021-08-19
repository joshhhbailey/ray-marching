///  @file MaterialNodeWidget.cpp
///  @brief Creates editable parameters widget for Material node

#include <QtWidgets/QFormLayout>

#include <ngl/Vec3.h>

#include "MaterialNodeWidget.h"

MaterialNodeWidget::MaterialNodeWidget()
{
    createWidgets();
    createLayouts();
    createConnections();
}

void MaterialNodeWidget::createWidgets()
{
    m_colourWidget = new Vec3Widget("RGB Colour:", ngl::Vec3(0.0, 0.0, 0.0));
    m_colourWidget->m_xField->setRange(0.0, 1.0);
    m_colourWidget->m_yField->setRange(0.0, 1.0);
    m_colourWidget->m_zField->setRange(0.0, 1.0);
    m_colourWidget->m_xField->setSingleStep(0.01);
    m_colourWidget->m_yField->setSingleStep(0.01);
    m_colourWidget->m_zField->setSingleStep(0.01);

    m_colourLabel = new QLabel();
    updateColourPreview();
}

void MaterialNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow(m_colourWidget);
    mainLayout->addRow(m_colourLabel);
    setLayout(mainLayout);
}

void MaterialNodeWidget::createConnections()
{
  connect(m_colourWidget->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateColourPreview()));
  connect(m_colourWidget->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateColourPreview()));
  connect(m_colourWidget->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateColourPreview()));
}

void MaterialNodeWidget::updateColourPreview()
{
    ngl::Vec3 RGB = m_colourWidget->getVec3();
    double r = RGB.m_x * 255.0f;
    double g = RGB.m_y * 255.0f;
    double b = RGB.m_z * 255.0f;

    m_palette.setColor(m_colourLabel->backgroundRole(), QColor(r, g, b) );
    m_colourLabel->setPalette(m_palette);
    m_colourLabel->setAutoFillBackground(true);
    m_colourLabel->repaint();
}