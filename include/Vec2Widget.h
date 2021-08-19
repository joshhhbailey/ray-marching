/// \brief Vec2 Widget embedded within node widget
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef VEC2WIDGET_H_
#define VEC2WIDGET_H_

#include <QtWidgets/QDoubleSpinBox>
#include <QLabel>

#include <ngl/Vec2.h>

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

#endif  // _VEC2WIDGET_H_