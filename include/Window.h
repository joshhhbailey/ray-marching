#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDockWidget>
#include <QtGui/QPalette>

#include "NGLScene.h"
#include "ShaderCodeContainer.h"
#include "NodeEditorContainer.h"
/*
#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;*/

class Window : public QMainWindow
{
public:
    Window(QApplication *_application);
    static QPalette *darkPalette();

private:
    void resizeEvent(QResizeEvent *_event) override;

    void createActions();
    void createMenuBar();
    void createWidgets();
    void createLayouts();
    void createConnections();

    QApplication *m_application;

    QAction *m_openFileAction;
    QAction *m_saveAction;
    QAction *m_saveAsAction;
    QAction *m_exitAction;

    QAction *m_shaderEditorAction;
    QAction *m_nodeEditorAction;

    QVBoxLayout *m_windowLayout;

    // Widgets
    QWidget *m_window;
    NGLScene *m_scene;

    NodeEditorContainer *m_nodeEditorContainer;
    QDockWidget *m_nodeEditorDock;
    //QtNodes::FlowScene *m_nodeEditorScene;
    //QtNodes::FlowView *m_nodeEditorView;

    ShaderCodeContainer *m_shaderCodeContainer;
    QDockWidget *m_shaderEditorDock;
};
