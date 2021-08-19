/// \brief Creates editable parameters widget for Plane node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef PLANENODEWIDGET_H_
#define PLANENODEWIDGET_H_

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

#endif  // _PLANENODEWIDGET_H_