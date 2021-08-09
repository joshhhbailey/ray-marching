#pragma once

#include <ngl/Vec2.h>

#include <QtWidgets/QDoubleSpinBox>
#include <QLabel>

class Vec2Widget : public QWidget
{
public:
    Vec2Widget(QString _label = QString("Vec2"), ngl::Vec2 _vec2 = {0.0f, 0.0f});
    
    ngl::Vec2 getVec2() const { return ngl::Vec2(m_xField->value(),
                                                 m_yField->value()); }

    void setVec2(ngl::Vec2 _vec2) { m_xField->setValue(_vec2.m_x);
                                    m_yField->setValue(_vec2.m_y); }
    
    QLabel *m_label;
    QDoubleSpinBox *m_xField;
    QDoubleSpinBox *m_yField;

private:
    void createWidgets();
    void createLayouts();
};