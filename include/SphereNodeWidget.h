/// \brief Creates editable parameters widget for Box node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef SPHERENODEWIDGET_H_
#define SPHERENODEWIDGET_H_

#include "MasterSDFNodeWidget.h"

class SphereNodeWidget : public MasterSDFNodeWidget
{
    Q_OBJECT
public:
    SphereNodeWidget();
    QDoubleSpinBox* getRadiusWidget() { return m_radiusWidget; }

private:
    void createWidgets() override;
    void createLayouts() override;

    QDoubleSpinBox *m_radiusWidget;
};

#endif  // _SPHERENODEWIDGET_H_