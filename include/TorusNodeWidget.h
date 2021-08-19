/// \brief Creates editable parameters widget for Torus node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef TORUSNODEWIDGET_H_
#define TORUSNODEWIDGET_H_

#include "MasterSDFNodeWidget.h"

class TorusNodeWidget : public MasterSDFNodeWidget
{
    Q_OBJECT
public:
    TorusNodeWidget();
    Vec2Widget* getRadiusWidget() { return m_radiusWidget; }

private:
    void createWidgets() override;
    void createLayouts() override;

    Vec2Widget *m_radiusWidget;
};

#endif  // _TORUSNODEWIDGET_H_