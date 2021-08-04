#include "UnionNodeWidget.h"

#include <QtWidgets/QFormLayout>

UnionNodeWidget::UnionNodeWidget()
{
    createWidgets();
    createLayouts();
}

void UnionNodeWidget::createWidgets()
{
    m_inspectCodeButton = new QPushButton("Inspect Code");
}

void UnionNodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow(m_inspectCodeButton);
    setLayout(mainLayout);
}