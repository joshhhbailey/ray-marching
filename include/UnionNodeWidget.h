#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>

class UnionNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    UnionNodeWidget();
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QPushButton *m_inspectCodeButton;
};