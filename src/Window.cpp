#include <iostream>
#include <QtWidgets/QMenuBar>
#include <QtGui/QColor>

#include "Window.h"

Window::Window()
{
    setWindowTitle("Ray Marching");
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    createActions();
    createMenuBar();
    createWidgets();
    createLayouts();
    createConnections();
}

void Window::createActions()
{
    m_shaderEditorAction = new QAction("Shader Editor");
}

void Window::createMenuBar()
{
    // Create menu
    setMenuBar(new QMenuBar());
    QMenu *windowsMenu = new QMenu("Windows");

    // Add action to menu
    windowsMenu->addAction(m_shaderEditorAction);
    menuBar()->addMenu(windowsMenu);
}

void Window::createWidgets()
{
    // Create Window widget
    m_windowWidget = new QWidget();
    setCentralWidget(m_windowWidget);

    // Create NGLScene widget
    m_scene = new NGLScene();

    // Create Container widget
    m_shaderEditorContainer = new ContainerWidget(m_scene);

    // Create dockable widget
    m_shaderEditorDock = new QDockWidget(tr("Shader Editor"), this);
    m_shaderEditorDock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);

    // Embed Container into dockable widget
    m_shaderEditorDock->setWidget(m_shaderEditorContainer);
    addDockWidget(Qt::RightDockWidgetArea, m_shaderEditorDock);
}

void Window::createLayouts()
{
    m_windowLayout = new QVBoxLayout();
    m_windowLayout->setContentsMargins(0, 0, 0, 0);
    m_windowLayout->addWidget(m_scene);
    m_windowWidget->setLayout(m_windowLayout);
}

void Window::createConnections()
{
    connect(m_shaderEditorAction, SIGNAL(triggered()), m_shaderEditorDock, SLOT(show()));
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