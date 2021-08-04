#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>

class PlaneNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    PlaneNodeWidget();
    QDoubleSpinBox* getYPosWidget() { return m_yPosWidget; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QDoubleSpinBox *m_yPosWidget;
    QPushButton *m_inspectCodeButton;
};