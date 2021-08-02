#include "SphereNodeWidget.h"

#include <QtWidgets/QFormLayout>

#include <ngl/Vec3.h>

SphereNodeWidget::SphereNodeWidget()
{
    setTitle("Properties:");
    createWidgets();
    createLayouts();
}

void SphereNodeWidget::createWidgets()
{
    m_positionWidget = new Vec3Widget("Position:", ngl::Vec3(0.0, 0.0, 0.0));
}

void SphereNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow(m_positionWidget);
    setLayout(mainLayout);
}