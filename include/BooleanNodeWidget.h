#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>

class BooleanNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    BooleanNodeWidget();
    QSpinBox* getIDWidget() { return m_idWidget; }
    QComboBox* getOperatorCB() { return m_changeOperatorCB; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QSpinBox *m_idWidget;
    QComboBox *m_changeOperatorCB;
    QPushButton *m_inspectCodeButton;
};