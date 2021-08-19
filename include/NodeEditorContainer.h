/// \brief Contains all widgets associated with the Node Editor
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef NODEEDITORCONTAINER_H_
#define NODEEDITORCONTAINER_H_

#include <QtWidgets/QWidget>

#include "NodeEditorWidget.h"
#include "NGLScene.h"

class NodeEditorContainer : public QWidget
{
    Q_OBJECT
public:
    NodeEditorContainer(NGLScene *_scene);

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();

private:
    void createWidgets();
    void createLayouts();

    NodeEditorWidget *m_nodeEditorWidget;

    NGLScene *m_scene;
};

#endif  // _NODEEDITORCONTAINER_H_