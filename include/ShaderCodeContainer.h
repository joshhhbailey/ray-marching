#include "ShaderCodeWidget.h"

#include "NGLScene.h"

#include <QtWidgets/QWidget>

class ShaderCodeContainer : public QWidget
{
    Q_OBJECT
public:
    ShaderCodeContainer(NGLScene *_scene);

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();

private:
    void createWidgets();
    void createLayouts();

    ShaderCodeWidget *m_shaderCodeWidget;

    QString m_filename;

    NGLScene *m_scene;
};