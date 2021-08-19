///  @file Vec3Widget.cpp
///  @brief Vec3 Widget embedded within node widget

#include <QtWidgets/QGridLayout>

#include "Vec3Widget.h"

Vec3Widget::Vec3Widget(QString _label, ngl::Vec3 _vec3)
{
    createWidgets();
    createLayouts();
    m_label->setText(_label);
    setVec3(_vec3);
}

void Vec3Widget::createWidgets()
{
    m_label = new QLabel;
    m_xField = new QDoubleSpinBox();
    m_yField = new QDoubleSpinBox();
    m_zField = new QDoubleSpinBox();
    m_xField->setRange(-9999.0, 9999.0);
    m_yField->setRange(-9999.0, 9999.0);
    m_zField->setRange(-9999.0, 9999.0);
}
void Vec3Widget::createLayouts()
{
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(m_label, 0, 0);
    mainLayout->addWidget(m_xField, 0, 1);
    mainLayout->addWidget(m_yField, 0, 2);
    mainLayout->addWidget(m_zField, 0, 3);
    setLayout(mainLayout);
}