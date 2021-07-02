#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDockWidget>
#include <QtGui/QPalette>

#include "NGLScene.h"
#include "ShaderCodeContainer.h"

class Window : public QMainWindow
{
public:
    Window(QApplication *_application);
    static QPalette *darkPalette();

private:
    void createActions();
    void createMenuBar();
    void createWidgets();
    void createLayouts();
    void createConnections();

    QApplication *m_application;
    NGLScene *m_scene;

    QAction *m_openFileAction;
    QAction *m_saveAction;
    QAction *m_saveAsAction;
    QAction *m_exitAction;

    QAction *m_shaderEditorAction;

    QDockWidget *m_shaderEditorDock;
    ShaderCodeContainer *m_shaderCodeContainer;

    QVBoxLayout *m_windowLayout;
    QWidget *m_windowWidget;
};
