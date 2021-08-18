#include "TorusNodeWidget.h"

#include <QtWidgets/QFormLayout>

#include <ngl/Vec2.h>
#include <ngl/Vec3.h>

TorusNodeWidget::TorusNodeWidget()
{
    createWidgets();
    createLayouts();
}

void TorusNodeWidget::createWidgets()
{
    m_idWidget = new QSpinBox();
    m_idWidget->setRange(0, 9999);
    m_idWidget->setValue(0);
    m_positionWidget = new Vec3Widget("Position:", ngl::Vec3(0.0f, 0.0f, 0.0f));
    m_radiusWidget = new Vec2Widget("Inner/Outer Radius:", ngl::Vec2(2.0f, 1.0f));
    m_inspectCodeButton = new QPushButton("Inspect Code");
}

void TorusNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow("ID:", m_idWidget);
    mainLayout->addRow(m_positionWidget);
    mainLayout->addRow(m_radiusWidget);
    mainLayout->addRow(m_inspectCodeButton);
    setLayout(mainLayout);
}