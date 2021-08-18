#include "BooleanNodeWidget.h"

#include <QtWidgets/QFormLayout>

BooleanNodeWidget::BooleanNodeWidget()
{
    createWidgets();
    createLayouts();
}

void BooleanNodeWidget::createWidgets()
{
    m_idWidget = new QSpinBox();
    m_idWidget->setRange(0, 9999);
    m_idWidget->setValue(0);
    m_idWidget->setEnabled(false);
    m_idWidget->hide();

    m_changeOperatorCB = new QComboBox();
    m_changeOperatorCB->addItem("Intersection");
    m_changeOperatorCB->addItem("Union");
    m_changeOperatorCB->addItem("Difference");

    m_inspectCodeButton = new QPushButton("Inspect Code");
}

void BooleanNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow("ID:", m_idWidget);
    mainLayout->addRow("Type:", m_changeOperatorCB);
    mainLayout->addRow(m_inspectCodeButton);
    setLayout(mainLayout);
}