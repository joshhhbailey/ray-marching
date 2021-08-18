#include "BoxNodeWidget.h"

#include <QtWidgets/QFormLayout>

#include <ngl/Vec3.h>

BoxNodeWidget::BoxNodeWidget()
{
    createWidgets();
    createLayouts();
}

void BoxNodeWidget::createWidgets()
{
    m_idWidget = new QSpinBox();
    m_idWidget->setRange(0, 9999);
    m_idWidget->setValue(0);
    m_positionWidget = new Vec3Widget("Position:", ngl::Vec3(0.0, 0.0, 0.0));
    m_sizeWidget = new Vec3Widget("Size:", ngl::Vec3(1.0, 1.0, 1.0));
    m_inspectCodeButton = new QPushButton("Inspect Code");
}

void BoxNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow("ID:", m_idWidget);
    mainLayout->addRow(m_positionWidget);
    mainLayout->addRow(m_sizeWidget);
    mainLayout->addRow(m_inspectCodeButton);
    setLayout(mainLayout);
}