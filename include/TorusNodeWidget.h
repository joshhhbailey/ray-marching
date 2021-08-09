#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>

#include "Vec2Widget.h"
#include "Vec3Widget.h"

class TorusNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    TorusNodeWidget();
    QSpinBox* getIDWidget() { return m_idWidget; }
    Vec3Widget* getPositionWidget() { return m_positionWidget; }
    Vec2Widget* getRadiusWidget() { return m_radiusWidget; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QSpinBox *m_idWidget;
    Vec3Widget *m_positionWidget;
    Vec2Widget *m_radiusWidget;
    QPushButton *m_inspectCodeButton;
};