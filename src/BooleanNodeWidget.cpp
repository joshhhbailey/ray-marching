#include "BooleanNodeWidget.h"

#include <QtWidgets/QFormLayout>

BooleanNodeWidget::BooleanNodeWidget()
{
    createWidgets();
    createLayouts();
}

void BooleanNodeWidget::createWidgets()
{
    m_changeOperatorCB = new QComboBox();
    m_changeOperatorCB->addItem("Intersection");
    m_changeOperatorCB->addItem("Union");
    m_changeOperatorCB->addItem("Difference");

    m_inspectCodeButton = new QPushButton("Inspect Code");
}

void BooleanNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow("Type:", m_changeOperatorCB);
    mainLayout->addRow(m_inspectCodeButton);
    setLayout(mainLayout);
}