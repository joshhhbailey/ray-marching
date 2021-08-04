#include "PlaneNodeWidget.h"

#include <QtWidgets/QFormLayout>

PlaneNodeWidget::PlaneNodeWidget()
{
    createWidgets();
    createLayouts();
}

void PlaneNodeWidget::createWidgets()
{
    m_yPosWidget = new QDoubleSpinBox();
    m_yPosWidget->setRange(-9999.0, 9999.0);
    m_yPosWidget->setValue(0.0);
    m_inspectCodeButton = new QPushButton("Inspect Code");
}

void PlaneNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow("Y Position:", m_yPosWidget);
    mainLayout->addRow(m_inspectCodeButton);
    setLayout(mainLayout);
}