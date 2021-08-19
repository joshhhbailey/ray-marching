/// \brief Creates editable parameters widget for boolean operator node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef BOOLEANNODEWIDGET_H_
#define BOOLEANNODEWIDGET_H_

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

#endif  // _BOOLEANNODEWIDGET_H_