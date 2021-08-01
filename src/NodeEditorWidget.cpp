#include "NodeEditorWidget.h"
#include "TestNode.h"
#include "SphereNode.h"
#include "RayMarchNode.h"

#include <QtWidgets/QFormLayout>
#include <QTime>

#include <iostream>
#include <QDebug>

#include <QtCore/QUuid>

NodeEditorWidget::NodeEditorWidget(NGLScene *_scene)
{
    m_scene = _scene;
    setTitle("Node Graph");
    createWidgets();
    createLayouts();
    createConnections();
    setupNodeGraph();
    startTimer(10);
}

void NodeEditorWidget::createWidgets()
{
    m_nodeEditorScene = new QtNodes::FlowScene(registerDataModels());
    m_nodeEditorView = new QtNodes::FlowView(m_nodeEditorScene);

    m_compileButton = new QPushButton("Compile");
    m_pauseButton = new QPushButton("Pause/Unpause");

    m_outputLabel = new QLabel();
    m_outputLabel->setText("[" + QTime::currentTime().toString() + "] Welcome to fragOut!");

    m_timerLabel = new QLabel();
}

void NodeEditorWidget::createLayouts()
{
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(m_nodeEditorView, 0, 0, 1, 2);
    mainLayout->addWidget(m_compileButton, 1, 0, 1, 1);
    mainLayout->addWidget(m_pauseButton, 1, 1, 1, 1);
    mainLayout->addWidget(m_outputLabel, 2, 0, 1, 2);
    mainLayout->addWidget(m_timerLabel, 3, 0, 1, 2);
    setLayout(mainLayout);
}

void NodeEditorWidget::createConnections()
{
    connect(m_compileButton, SIGNAL(clicked()), this, SLOT(compileButtonClicked()));
    connect(m_pauseButton, SIGNAL(clicked()), this, SLOT(pauseButtonClicked()));
}

void NodeEditorWidget::setupNodeGraph()
{
    m_nodeEditorScene->createNode(std::make_unique<RayMarchNode>());
}

std::shared_ptr<DataModelRegistry> NodeEditorWidget::registerDataModels()
{
    std::shared_ptr<DataModelRegistry> dataModels = std::make_shared<DataModelRegistry>();
    
    dataModels->registerModel<TestNode>("Tests");
    dataModels->registerModel<SphereNode>("SDFs");
    dataModels->registerModel<RayMarchNode>("RayMarching");

    /*dataModels->registerModel<Union>("Boolean Operators");
    dataModels->registerModel<Intersection>("Boolean Operators");
    dataModels->registerModel<Difference>("Boolean Operators");*/

  return dataModels;
}

void NodeEditorWidget::setStyle()
{
  ConnectionStyle::setConnectionStyle(
    R"(
  {
    "ConnectionStyle": {
      "UseDataDefinedColors": true
    }
  }
  )");
}

void NodeEditorWidget::compileButtonClicked()
{
    std::cout << "Retrieving shader code...\n";

    std::vector<Node*> nodes = m_nodeEditorScene->allNodes();
    for (int i = 0; i < nodes.size(); ++i)
    {
        std::cout << nodes[i] << std::endl;
    }

    QUuid id = nodes[0]->id();
    qDebug() << id;
    std::shared_ptr<ShaderCodeData> test = std::dynamic_pointer_cast<ShaderCodeData>(nodes[1]->nodeDataModel()->outData(0));
    
    qDebug() << nodes[1]->nodeDataModel()->name();
    qDebug() << test->getVariableName();
    std::cout << test->getShaderCode().toStdString() << std::endl;

    QString string = "] ";

    if (m_scene->compileShaderCode(test->getShaderCode(), false))
    {
        m_firstCompile = true;
        string += "Shader compilation successful!";
        m_pausedTime = 0;
        m_pauseTime = false;
    }
    else
    {
        std::vector<GLchar> error = m_scene->getShaderErrorMessage();
        for (int i = 0; i < error.size(); ++i)
        {
            string += error[i];
        }
    }
    m_outputLabel->setText("[" + QTime::currentTime().toString() + string);
}

void NodeEditorWidget::pauseButtonClicked()
{
    if (!m_pauseTime)
    {
        m_pausedTime += m_scene->pauseNodesTime();
        m_pauseTime = true;
    }
    else
    {
        m_scene->unpauseNodesTime(m_pausedTime);
        m_pauseTime = false;
    }
}

void NodeEditorWidget::timerEvent(QTimerEvent *_event)
{
    // Update compilation timer
    if (!m_pauseTime)
    {
        QString compTime;
        if (m_firstCompile)
        {
            compTime = QString::number(m_scene->getNodesCompilationTime() + (m_pausedTime / 1000.0f));
        }
        else
        {
            compTime = "0.000";
        }
        m_timerLabel->setText(compTime);
    }

    update();
}