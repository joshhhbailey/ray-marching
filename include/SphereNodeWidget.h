/// \brief Creates editable parameters widget for Box node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef SPHERENODEWIDGET_H_
#define SPHERENODEWIDGET_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>

#include "Vec3Widget.h"

class SphereNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    SphereNodeWidget();
    QSpinBox* getIDWidget() { return m_idWidget; }
    Vec3Widget* getPositionWidget() { return m_positionWidget; }
    QDoubleSpinBox* getRadiusWidget() { return m_radiusWidget; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QSpinBox *m_idWidget;
    Vec3Widget *m_positionWidget;
    QDoubleSpinBox *m_radiusWidget;
    QPushButton *m_inspectCodeButton;
};

#endif  // _SPHERENODEWIDGET_H_