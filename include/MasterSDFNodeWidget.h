/// \brief Handles logic for SDF node widgets
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef MASTERSDFNODEWIDGET_H_
#define MASTERSDFNODEWIDGET_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>

#include "Vec2Widget.h"
#include "Vec3Widget.h"

class MasterSDFNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    MasterSDFNodeWidget() {}

    QSpinBox *m_idWidget;
    Vec3Widget *m_positionWidget;
    QPushButton *m_inspectCodeButton;

private:
    virtual void createWidgets() {}
    virtual void createLayouts() {}
};

#endif  // MASTERSDFNODEWIDGET_H_