#include "NodeEditorWidget.h"

#include "SphereNode.h"
#include "PlaneNode.h"
#include "RayMarchNode.h"
#include "UnionNode.h"

#include <QtWidgets/QFormLayout>
#include <QTime>

#include <iostream>

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
    
    dataModels->registerModel<SphereNode>("SDFs");
    dataModels->registerModel<PlaneNode>("SDFs");
    dataModels->registerModel<RayMarchNode>("RayMarching");
    dataModels->registerModel<UnionNode>("Boolean Operators");
    /*dataModels->registerModel<IntersectionNode>("Boolean Operators");
    dataModels->registerModel<DifferenceNode>("Boolean Operators");*/

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

    // Get all nodes from node graph
    std::vector<Node*> nodes = m_nodeEditorScene->allNodes();

    std::shared_ptr<ShaderCodeData> rmNodeData;
    NodeValidationState rmState;
    int rmNodes = 0;

    // Find RayMarch node
    for (int i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i]->nodeDataModel()->name() == "Ray March")
        {
            rmNodeData = std::dynamic_pointer_cast<ShaderCodeData>(nodes[i]->nodeDataModel()->outData(0));
            rmState = nodes[i]->nodeDataModel()->validationState();
            rmNodes++;
        }
    }

    QString string = "] ";
    if (rmNodeData != nullptr)
    {
        if (rmNodes > 1)
        {
            string += "Only ONE Ray March node is allowed!";
        }
        else
        {
            if (rmState == NodeValidationState::Valid)
            {
                if (m_scene->compileShaderCode(rmNodeData->getShaderCode(), false))
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
            }
            else
            {
                string += "Ray March node is missing inputs!";
            }
        }
    }
    else
    {
        string += "Could not find Ray March node!";
    }
    m_outputLabel->setText("[" + QTime::currentTime().toString() + string);
}

void NodeEditorWidget::pauseButtonClicked()
{
    if (!m_scene->getShaderEditor())
    {
        if (!m_pauseTime)
        {
            m_pausedTime += m_scene->pauseTime();
            m_pauseTime = true;
        }
        else
        {
            m_scene->unpauseTime(m_pausedTime);
            m_pauseTime = false;
        }
    }
}

void NodeEditorWidget::timerEvent(QTimerEvent *_event)
{
    // Update compilation timer
    if (!m_scene->getShaderEditor())
    {
        if (!m_pauseTime)
        {
            QString compTime;
            if (m_firstCompile)
            {
                compTime = QString::number(m_scene->getCompilationTime() + (m_pausedTime / 1000.0f));
            }
            else
            {
                compTime = "0.000";
            }
            m_timerLabel->setText(compTime);
        }
    }
    else
    {
        m_timerLabel->setText("0.000");
    }
    update();
}