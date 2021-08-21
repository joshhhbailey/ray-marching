///  @file PlaneNode.cpp
///  @brief Handles logic for Plane node

#include "PlaneNode.h"

PlaneNode::PlaneNode()
{
    m_variableName = "plane0";
    m_materialMap.insert(m_variableName, ngl::Vec3(1.0f, 1.0f, 1.0f));
    QString shaderCode = "float " + m_variableName + " = sdPlane(_p, 0);\n";
    QString functionCall = " = sdPlane(_p, 0);\n";

    m_nodeData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_nodeData->setIsSDF(true);
    m_nodeData->setFunctionCall(functionCall);

    m_planeWidget = new PlaneNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setWindowTitle("Plane Node");
    m_codeEditor->setPlainText(shaderCode);
    m_codeEditor->setReadOnly(true);
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void PlaneNode::createConnections()
{
  connect(m_planeWidget->getIDWidget(), SIGNAL(valueChanged(int)), this, SLOT(updateNode()));
  connect(m_planeWidget->getYPosWidget(), SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_planeWidget->getInspectCodeButton(), SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString PlaneNode::caption() const
{
    return QString("Infinite Plane");
}

QString PlaneNode::name() const
{
    return QString("Infinite Plane");
}

std::shared_ptr<NodeData> PlaneNode::outData(PortIndex)
{
    return m_nodeData;
}

QWidget* PlaneNode::embeddedWidget()
{
    return m_planeWidget;
}

QJsonObject PlaneNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_nodeData)
  {
    modelJson["shaderCode"] = m_nodeData->getShaderCode();
    modelJson["variableName"] = m_nodeData->getVariableName();
    modelJson["yPos"] = m_planeWidget->getYPosWidget()->value();
    modelJson["id"] = m_planeWidget->getIDWidget()->value();
  }

  return modelJson;
}

void PlaneNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue yp = _p["yPos"];
  QJsonValue id = _p["id"];

  m_nodeData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_nodeData->setShaderCode(shaderCode);
  }

  if (!vn.isUndefined())
  {
    QString variableName = vn.toString();
    m_nodeData->setVariableName(variableName);
  }

  if (!yp.isUndefined())
  {
    double yPos = yp.toDouble();
    m_planeWidget->getYPosWidget()->setValue(yPos);
  }

  if (!id.isUndefined())
  {
    m_planeWidget->getIDWidget()->setValue(id.toInt());
  }

  m_nodeData->setIsSDF(true);
}

void PlaneNode::updateNode()
{
  // Setup variables
  double yPos = m_planeWidget->getYPosWidget()->value();

  // Convert to string
  QString position = QString::number(yPos);

  // Update node data
  m_variableName = "plane" + QString::number(m_planeWidget->getIDWidget()->value());
  m_nodeData->setVariableName(m_variableName);

  QString shaderCode = "float " + m_variableName + " = sdPlane(_p, " + position + ");\n";
  m_nodeData->setShaderCode(shaderCode);

  QString functionCall = " = sdPlane(_p, " + position + ");\n";
  m_nodeData->setFunctionCall(functionCall);

  if (m_receivedNode)
  {
    m_materialMap.clear();
    m_materialMap.insert(m_variableName, m_receivedNode->getMaterial());
    m_nodeData->setMaterialMap(m_materialMap);
  }

  // Tell connected node to update received data
  Q_EMIT dataUpdated(0);
}

void PlaneNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}