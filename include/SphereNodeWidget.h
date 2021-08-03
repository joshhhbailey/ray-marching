#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>

#include "Vec3Widget.h"

class SphereNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    SphereNodeWidget();
    Vec3Widget* getPositionWidget() { return m_positionWidget; }
    QDoubleSpinBox* getRadiusWidget() { return m_radiusWidget; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    Vec3Widget *m_positionWidget;
    QDoubleSpinBox *m_radiusWidget;
    QPushButton *m_inspectCodeButton;
};