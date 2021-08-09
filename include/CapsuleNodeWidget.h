#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>

#include "Vec3Widget.h"

class CapsuleNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    CapsuleNodeWidget();
    QSpinBox* getIDWidget() { return m_idWidget; }
    Vec3Widget* getPositionAWidget() { return m_positionAWidget; }
    Vec3Widget* getPositionBWidget() { return m_positionBWidget; }
    QDoubleSpinBox* getRadiusWidget() { return m_radiusWidget; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QSpinBox *m_idWidget;
    Vec3Widget *m_positionAWidget;
    Vec3Widget *m_positionBWidget;
    QDoubleSpinBox *m_radiusWidget;
    QPushButton *m_inspectCodeButton;
};