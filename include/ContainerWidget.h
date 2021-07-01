#include "ShaderCodeWidget.h"

#include "NGLScene.h"

#include <QtWidgets/QWidget>

class ContainerWidget : public QWidget
{
public:
    ContainerWidget(NGLScene *_scene);

private:
    void createWidgets();
    void createLayouts();

    ShaderCodeWidget *m_shaderCodeWidget;

    NGLScene *m_scene;
};