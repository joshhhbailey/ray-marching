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

    startTimer(10);
}

void Window::timerEvent(QTimerEvent *_event)
{
    // When docked limit window width (25-50%), otherwise uncapped
    if (!m_shaderEditorDock->isWindow())
    {
        m_shaderEditorDock->setMinimumWidth(size().width() / 4);
        m_shaderEditorDock->setMaximumWidth(size().width() / 2);
    }
    else
    {
        m_shaderEditorDock->setMinimumWidth(0);
        m_shaderEditorDock->setMaximumWidth(QWIDGETSIZE_MAX);
    }
    if (!m_nodeEditorDock->isWindow())
    {
        m_nodeEditorDock->setMinimumWidth(size().width() / 4);
        m_nodeEditorDock->setMaximumWidth(size().width() / 2);
    }
    else
    {
        m_nodeEditorDock->setMinimumWidth(0);
        m_nodeEditorDock->setMaximumWidth(QWIDGETSIZE_MAX);
    }

    update();
}

void Window::createActions()
{
    // Shader editor
    m_newGLSLAction = new QAction("GLSL Shader");
    m_openGLSLAction = new QAction("GLSL Shader");
    m_saveGLSLAction = new QAction("GLSL Shader");
    m_saveAsGLSLAction = new QAction("GLSL Shader");

    // Node editor
    m_newNodesAction = new QAction("Node Graph");
    m_openNodesAction = new QAction("Node Graph");
    m_saveNodesAction = new QAction("Node Graph");
    m_saveAsNodesAction = new QAction("Node Graph");
    
    // Other
    m_exitAction = new QAction("Exit");
    m_shaderEditorAction = new QAction("Shader Editor");
    m_nodeEditorAction = new QAction("Node Editor");
    m_aboutAction = new QAction("About");
}

void Window::createMenuBar()
{
    // Create menus
    setMenuBar(new QMenuBar());
    QMenu *newMenu = new QMenu("New...");
    QMenu *fileMenu = new QMenu("File");
    QMenu *openMenu = new QMenu("Open...");
    QMenu *saveMenu = new QMenu("Save");
    QMenu *saveAsMenu = new QMenu("Save As...");
    QMenu *windowsMenu = new QMenu("Windows");
    QMenu *helpMenu = new QMenu("Help");

    // Add actions to menus
    newMenu->addAction(m_newGLSLAction);
    newMenu->addAction(m_newNodesAction);

    openMenu->addAction(m_openGLSLAction);
    openMenu->addAction(m_openNodesAction);

    saveMenu->addAction(m_saveGLSLAction);
    saveMenu->addAction(m_saveNodesAction);

    saveAsMenu->addAction(m_saveAsGLSLAction);
    saveAsMenu->addAction(m_saveAsNodesAction);

    fileMenu->addMenu(newMenu);
    fileMenu->addSeparator();
    fileMenu->addMenu(openMenu);
    fileMenu->addSeparator();
    fileMenu->addMenu(saveMenu);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(m_exitAction);

    windowsMenu->addAction(m_shaderEditorAction);
    windowsMenu->addAction(m_nodeEditorAction);

    helpMenu->addAction(m_aboutAction);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(windowsMenu);
    menuBar()->addMenu(helpMenu);
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
    m_nodeEditorContainer = new NodeEditorContainer(m_scene);
    m_nodeEditorDock = new QDockWidget(tr("Node Editor"), this);
    m_nodeEditorDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    m_nodeEditorDock->setWidget(m_nodeEditorContainer);
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
    // Shader Editor
    connect(m_newGLSLAction, SIGNAL(triggered()), m_shaderCodeContainer, SLOT(newFile()));
    connect(m_openGLSLAction, SIGNAL(triggered()), m_shaderCodeContainer, SLOT(openFile()));
    connect(m_saveGLSLAction, SIGNAL(triggered()), m_shaderCodeContainer, SLOT(saveFile()));
    connect(m_saveAsGLSLAction, SIGNAL(triggered()), m_shaderCodeContainer, SLOT(saveAsFile()));

    // Node Editor
    connect(m_newNodesAction, SIGNAL(triggered()), m_nodeEditorContainer, SLOT(newFile()));
    connect(m_openNodesAction, SIGNAL(triggered()), m_nodeEditorContainer, SLOT(openFile()));
    connect(m_saveNodesAction, SIGNAL(triggered()), m_nodeEditorContainer, SLOT(saveFile()));
    connect(m_saveAsNodesAction, SIGNAL(triggered()), m_nodeEditorContainer, SLOT(saveAsFile()));

    // Other
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