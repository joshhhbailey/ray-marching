#include "ShaderCodeWidget.h"

#include <QtWidgets/QWidget>

class ContainerWidget : public QWidget
{
public:
    ContainerWidget();

private:
    void createWidgets();
    void createLayouts();

    ShaderCodeWidget *m_shaderCodeWidget;
};