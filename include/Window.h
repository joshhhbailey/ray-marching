#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDockWidget>
#include <QtGui/QPalette>

#include "NGLScene.h"
#include "ContainerWidget.h"

class Window : public QMainWindow
{
public:
    Window();
    static QPalette *darkPalette();

private:
    void createActions();
    void createMenuBar();
    void createWidgets();
    void createLayouts();
    void createConnections();

    NGLScene *m_scene;
    QAction *m_shaderEditorAction;
    QDockWidget *m_shaderEditorDock;
    ContainerWidget *m_shaderEditorContainer;
    QVBoxLayout *m_windowLayout;
    QWidget *m_windowWidget;
};
