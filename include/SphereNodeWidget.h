#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QLabel>

#include "Vec3Widget.h"

class SphereNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    SphereNodeWidget();
    Vec3Widget* getPositionWidget() { return m_positionWidget; }

    QDoubleSpinBox* getRadiusWidget() { return m_radiusWidget; }

private:
    void createWidgets();
    void createLayouts();

    Vec3Widget *m_positionWidget;
    QDoubleSpinBox *m_radiusWidget;
};