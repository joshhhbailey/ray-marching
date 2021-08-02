#pragma once

#include <QtWidgets/QGroupBox>

#include "Vec3Widget.h"

class SphereNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    SphereNodeWidget();
    Vec3Widget* getPositionWidget() { return m_positionWidget; }

private:
    void createWidgets();
    void createLayouts();

    Vec3Widget *m_positionWidget;
};