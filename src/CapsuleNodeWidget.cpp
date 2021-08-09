#include "CapsuleNodeWidget.h"

#include <QtWidgets/QFormLayout>

#include <ngl/Vec3.h>

CapsuleNodeWidget::CapsuleNodeWidget()
{
    createWidgets();
    createLayouts();
}

void CapsuleNodeWidget::createWidgets()
{
    m_idWidget = new QSpinBox();
    m_idWidget->setRange(0, 9999);
    m_idWidget->setValue(0);
    m_positionAWidget = new Vec3Widget("Start Position:", ngl::Vec3(0.0, 0.0, 0.0));
    m_positionBWidget = new Vec3Widget("End Position:", ngl::Vec3(0.0, 0.0, 0.0));
    m_radiusWidget = new QDoubleSpinBox();
    m_radiusWidget->setRange(0.0, 9999.0);
    m_radiusWidget->setValue(1.0);
    m_inspectCodeButton = new QPushButton("Inspect Code");
}

void CapsuleNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow("ID:", m_idWidget);
    mainLayout->addRow(m_positionAWidget);
    mainLayout->addRow(m_positionBWidget);
    mainLayout->addRow("Radius:", m_radiusWidget);
    mainLayout->addRow(m_inspectCodeButton);
    setLayout(mainLayout);
}