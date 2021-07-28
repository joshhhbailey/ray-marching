#include "NodeEditorWidget.h"

#include "NGLScene.h"

#include <QtWidgets/QWidget>

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