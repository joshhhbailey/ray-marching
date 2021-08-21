///  @file SphereNode.cpp
///  @brief Handles logic for Sphere node

#include "SphereNode.h"

SphereNode::SphereNode()
{
    m_variableName = "sphere0";
    m_materialMap.insert(m_variableName, ngl::Vec3(1.0f, 1.0f, 1.0f));
    QString shaderCode = "float " + m_variableName + " = sdSphere(_p, vec3(0, 0, 0), 1.0);\n";
    QString functionCall = " = sdSphere(_p, vec3(0, 0, 0), 1.0);\n";

    m_nodeData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_nodeData->setIsSDF(true);
    m_nodeData->setFunctionCall(functionCall);

    m_sphereWidget = new SphereNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setWindowTitle("Sphere Node");
    m_codeEditor->setPlainText(shaderCode);
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void SphereNode::createConnections()
{
  connect(m_sphereWidget->m_idWidget, SIGNAL(valueChanged(int)), this, SLOT(updateNode()));
  connect(m_sphereWidget->m_positionWidget->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_sphereWidget->m_positionWidget->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_sphereWidget->m_positionWidget->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_sphereWidget->getRadiusWidget(), SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_sphereWidget->m_inspectCodeButton, SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString SphereNode::caption() const
{
    return QString("Sphere");
}

QString SphereNode::name() const
{
    return QString("Sphere");
}

std::shared_ptr<NodeData> SphereNode::outData(PortIndex)
{
    return m_nodeData;
}

QWidget* SphereNode::embeddedWidget()
{
    return m_sphereWidget;
}

QJsonObject SphereNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_nodeData)
  {
    modelJson["shaderCode"] = m_nodeData->getShaderCode();
    modelJson["variableName"] = m_nodeData->getVariableName();
    modelJson["xPos"] = m_sphereWidget->m_positionWidget->getVec3().m_x;
    modelJson["yPos"] = m_sphereWidget->m_positionWidget->getVec3().m_y;
    modelJson["zPos"] = m_sphereWidget->m_positionWidget->getVec3().m_z;
    modelJson["radius"] = m_sphereWidget->getRadiusWidget()->value();
    modelJson["id"] = m_sphereWidget->m_idWidget->value();
  }

  return modelJson;
}

void SphereNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue xp = _p["xPos"];
  QJsonValue yp = _p["yPos"];
  QJsonValue zp = _p["zPos"];
  QJsonValue r  = _p["radius"];
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

  if (!xp.isUndefined() && !yp.isUndefined() && !zp.isUndefined())
  {
    ngl::Vec3 position = ngl::Vec3(xp.toDouble(), yp.toDouble(), zp.toDouble());
    m_sphereWidget->m_positionWidget->setVec3(position);
  }

  if (!r.isUndefined())
  {
    m_sphereWidget->getRadiusWidget()->setValue(r.toDouble());
  }

  if (!id.isUndefined())
  {
    m_sphereWidget->m_idWidget->setValue(id.toInt());
  }

  m_nodeData->setIsSDF(true);
}

void SphereNode::updateNode()
{
  // Setup variables
  ngl::Vec3 pos = m_sphereWidget->m_positionWidget->getVec3();
  double x = pos.m_x;
  double y = pos.m_y;
  double z = pos.m_z;

  // Convert to string
  QString position = QString::number(x) + ", " + QString::number(y) + ", " + QString::number(z);
  QString radius = QString::number(m_sphereWidget->getRadiusWidget()->value());

  // Update node data
  m_variableName = "sphere" + QString::number(m_sphereWidget->m_idWidget->value());
  m_nodeData->setVariableName(m_variableName);

  QString shaderCode = "float " + m_variableName + " = sdSphere(_p, vec3(" + position + "), " + radius + ");\n";
  m_nodeData->setShaderCode(shaderCode);

  QString functionCall = " = sdSphere(_p, vec3(" + position + "), " + radius + ");\n";
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

void SphereNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}