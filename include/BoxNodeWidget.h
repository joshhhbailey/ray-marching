/// \brief Creates editable parameters widget for Box node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef BOXNODEWIDGET_H_
#define BOXNODEWIDGET_H_

#include "MasterSDFNodeWidget.h"

class BoxNodeWidget : public MasterSDFNodeWidget
{
    Q_OBJECT
public:
    BoxNodeWidget();
    Vec3Widget* getSizeWidget() { return m_sizeWidget; }

private:
    void createWidgets() override;
    void createLayouts() override;

    Vec3Widget *m_sizeWidget;
};

#endif  // _BOXNODEWIDGET_H_