#include <iostream>
#include <QtWidgets/QMenuBar>
#include <QtGui/QColor>
#include <QFileDialog>
#include <QtWidgets/QApplication>

#include "Window.h"

Window::Window(QApplication *_application)
{
    m_application = _application;
    setWindowTitle("fragOut!");
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    createActions();
    createMenuBar();
    createWidgets();
    createLayouts();
    createConnections();
}

void Window::resizeEvent(QResizeEvent *_event)
{
    m_shaderEditorDock->setMinimumWidth(size().width() / 4);
    m_shaderEditorDock->setMaximumWidth(size().width() / 2);
    m_nodeEditorDock->setMinimumWidth(size().width() / 4);
    m_nodeEditorDock->setMaximumWidth(size().width() / 2);
}

void Window::createActions()
{
    m_openFileAction = new QAction("Open file...");
    m_saveAction = new QAction("Save");
    m_saveAsAction = new QAction("Save as...");
    m_exitAction = new QAction("Exit");

    m_shaderEditorAction = new QAction("Shader Editor");
    m_nodeEditorAction = new QAction("Node Editor");
}

void Window::createMenuBar()
{
    // Create menus
    setMenuBar(new QMenuBar());
    QMenu *fileMenu = new QMenu("File");
    QMenu *windowsMenu = new QMenu("Windows");

    // Add actions to menus
    fileMenu->addAction(m_openFileAction);
    fileMenu->addAction(m_saveAction);
    fileMenu->addAction(m_saveAsAction);
    fileMenu->addAction(m_exitAction);

    windowsMenu->addAction(m_shaderEditorAction);
    windowsMenu->addAction(m_nodeEditorAction);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(windowsMenu);
}

void Window::createWidgets()
{
    // Create Window widget
    m_window = new QWidget();
    setCentralWidget(m_window);

    // Create NGLScene widget
    m_scene = new NGLScene();

    // Create Shader Code Container dockable widget
    m_shaderCodeContainer = new ShaderCodeContainer(m_scene);
    m_shaderEditorDock = new QDockWidget(tr("Shader Editor"), this);
    m_shaderEditorDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    m_shaderEditorDock->setWidget(m_shaderCodeContainer);
    addDockWidget(Qt::RightDockWidgetArea, m_shaderEditorDock);

    // Create Node Editor Container dockable widget
    m_nodeEditorContainer = new NodeEditorContainer();
    //m_nodeEditorScene = new QtNodes::FlowScene(registerDataModels(), m_window);
    //m_nodeEditorView = new QtNodes::FlowView(m_nodeEditorScene);
    m_nodeEditorDock = new QDockWidget(tr("Node Editor"), this);
    m_nodeEditorDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    //m_nodeEditorDock->setWidget(m_nodeEditorView);
    addDockWidget(Qt::LeftDockWidgetArea, m_nodeEditorDock);
    m_nodeEditorDock->hide();
}

void Window::createLayouts()
{
    m_windowLayout = new QVBoxLayout();
    m_windowLayout->setContentsMargins(0, 0, 0, 0);
    m_windowLayout->addWidget(m_scene);
    m_window->setLayout(m_windowLayout);
}

void Window::createConnections()
{
    connect(m_openFileAction, SIGNAL(triggered()), m_shaderCodeContainer, SLOT(openFile()));
    connect(m_saveAction, SIGNAL(triggered()), m_shaderCodeContainer, SLOT(saveFile()));
    connect(m_saveAsAction, SIGNAL(triggered()), m_shaderCodeContainer, SLOT(saveAsFile()));
    connect(m_exitAction, SIGNAL(triggered()), m_application, SLOT(quit()));

    connect(m_shaderEditorAction, SIGNAL(triggered()), m_shaderEditorDock, SLOT(show()));
    connect(m_nodeEditorAction, SIGNAL(triggered()), m_nodeEditorDock, SLOT(show()));
}

QPalette *Window::darkPalette()
{
    QPalette *darkPalette = new QPalette();
    darkPalette->setColor(QPalette::Window, QColor(45, 45, 45));
    darkPalette->setColor(QPalette::WindowText, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette->setColor(QPalette::AlternateBase, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::ToolTipBase, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::Text, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::Button, QColor(45, 45, 45));
    darkPalette->setColor(QPalette::ButtonText, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::BrightText, Qt::red);
    darkPalette->setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette->setColor(QPalette::Link, Qt::gray);
    return darkPalette;
}

/*static std::shared_ptr<DataModelRegistry> registerDataModels()
{
  auto ret = std::make_shared<DataModelRegistry>();

  ret->registerModel<NaiveDataModel>();

  /*
     We could have more models registered.
     All of them become items in the context meny of the scene.

     ret->registerModel<AnotherDataModel>();
     ret->registerModel<OneMoreDataModel>();

   //

  return ret;
}


static void setStyle()
{
  ConnectionStyle::setConnectionStyle(
    R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");
}*/