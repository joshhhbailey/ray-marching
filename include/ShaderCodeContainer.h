/// \brief Contains all widgets associated with the Shader Code Editor
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef SHADERCODECONTAINER_H_
#define SHADERCODECONTAINER_H_

#include <QtWidgets/QWidget>

#include "ShaderCodeWidget.h"
#include "NGLScene.h"

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

#endif  // _SHADERCODECONTAINER_H_