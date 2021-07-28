#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDockWidget>
#include <QtGui/QPalette>

#include "NGLScene.h"
#include "ShaderCodeContainer.h"
#include "NodeEditorContainer.h"

class Window : public QMainWindow
{
public:
    Window(QApplication *_application);
    static QPalette *darkPalette();

private:
    void timerEvent(QTimerEvent *_event) override;

    void createActions();
    void createMenuBar();
    void createWidgets();
    void createLayouts();
    void createConnections();

    QApplication *m_application;

    // Shader Editor
    QAction *m_newGLSLAction;
    QAction *m_openGLSLAction;
    QAction *m_saveGLSLAction;
    QAction *m_saveAsGLSLAction;

    // Node Editor
    QAction *m_newNodesAction;
    QAction *m_openNodesAction;
    QAction *m_saveNodesAction;
    QAction *m_saveAsNodesAction;

    QAction *m_exitAction;

    QAction *m_shaderEditorAction;
    QAction *m_nodeEditorAction;

    QAction *m_aboutAction;

    QVBoxLayout *m_windowLayout;

    // Widgets
    QWidget *m_window;
    NGLScene *m_scene;

    NodeEditorContainer *m_nodeEditorContainer;
    QDockWidget *m_nodeEditorDock;

    ShaderCodeContainer *m_shaderCodeContainer;
    QDockWidget *m_shaderEditorDock;
};
