#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QLabel>

#include "Vec3Widget.h"

class RayMarchNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    RayMarchNodeWidget();
    Vec3Widget* getRayOriginWidget() { return m_rayOriginWidget; }
    Vec3Widget* getLightPositionWidget() { return m_lightPositionWidget; }

private:
    void createWidgets();
    void createLayouts();

    QLabel *m_rayOriginLabel;
    Vec3Widget *m_rayOriginWidget;
    QLabel *m_lightLabel;
    Vec3Widget *m_lightPositionWidget;
};