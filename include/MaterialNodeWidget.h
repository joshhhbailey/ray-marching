#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QPalette>

#include "Vec3Widget.h"

class MaterialNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    MaterialNodeWidget();
    Vec3Widget* getColourWidget() { return m_colourWidget; }

public slots:
    void updateColourPreview();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();

    Vec3Widget *m_colourWidget;
    QLabel *m_colourLabel;
    QPalette m_palette;
};