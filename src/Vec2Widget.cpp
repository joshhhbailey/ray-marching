#include "Vec2Widget.h"
#include <QtWidgets/QGridLayout>

Vec2Widget::Vec2Widget(QString _label, ngl::Vec2 _vec2)
{
    createWidgets();
    createLayouts();
    m_label->setText(_label);
    setVec2(_vec2);
}

void Vec2Widget::createWidgets()
{
    m_label = new QLabel;
    m_xField = new QDoubleSpinBox();
    m_yField = new QDoubleSpinBox();
    m_xField->setRange(-9999.0, 9999.0);
    m_yField->setRange(-9999.0, 9999.0);
}
void Vec2Widget::createLayouts()
{
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(m_label, 0, 0);
    mainLayout->addWidget(m_xField, 0, 1);
    mainLayout->addWidget(m_yField, 0, 2);
    setLayout(mainLayout);
}