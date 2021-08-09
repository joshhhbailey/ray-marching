#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>

class BooleanNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    BooleanNodeWidget();
    QComboBox* getOperatorCB() { return m_changeOperatorCB; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QComboBox *m_changeOperatorCB;
    QPushButton *m_inspectCodeButton;
};