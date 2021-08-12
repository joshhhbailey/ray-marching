#pragma once

#include <QtWidgets/QGroupBox>

#include "Vec3Widget.h"

class MaterialNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    MaterialNodeWidget();
    Vec3Widget* getColourWidget() { return m_colourWidget; }

private:
    void createWidgets();
    void createLayouts();

    Vec3Widget *m_colourWidget;
};