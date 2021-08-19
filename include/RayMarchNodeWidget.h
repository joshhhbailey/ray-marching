/// \brief Creates editable parameters widget for Ray March node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef RAYMARCHNODEWIDGET_H_
#define RAYMARCHNODEWIDGET_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

#include "Vec3Widget.h"

class RayMarchNodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    RayMarchNodeWidget();

    Vec3Widget* getRayOriginWidget() { return m_rayOriginWidget; }
    Vec3Widget* getLightPositionWidget() { return m_lightPositionWidget; }
    QPushButton* getInspectCodeButton() { return m_inspectCodeButton; }

private:
    void createWidgets();
    void createLayouts();

    QLabel *m_rayOriginLabel;
    Vec3Widget *m_rayOriginWidget;
    QLabel *m_lightLabel;
    Vec3Widget *m_lightPositionWidget;
    QPushButton *m_inspectCodeButton;
};

#endif  // _RAYMARCHNODEWIDGET_H_