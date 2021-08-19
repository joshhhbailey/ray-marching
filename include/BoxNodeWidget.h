/// \brief Creates editable parameters widget for Box node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef BOXNODEWIDGET_H_
#define BOXNODEWIDGET_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>

#include "Vec3Widget.h"

class BoxNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    BoxNodeWidget();
    QSpinBox* getIDWidget() { return m_idWidget; }
    Vec3Widget* getPositionWidget() { return m_positionWidget; }
    Vec3Widget* getSizeWidget() { return m_sizeWidget; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QSpinBox *m_idWidget;
    Vec3Widget *m_positionWidget;
    Vec3Widget *m_sizeWidget;
    QPushButton *m_inspectCodeButton;
};

#endif  // _BOXNODEWIDGET_H_