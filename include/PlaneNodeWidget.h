#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>

class PlaneNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    PlaneNodeWidget();
    QSpinBox* getIDWidget() { return m_idWidget; }
    QDoubleSpinBox* getYPosWidget() { return m_yPosWidget; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QSpinBox *m_idWidget;
    QDoubleSpinBox *m_yPosWidget;
    QPushButton *m_inspectCodeButton;
};