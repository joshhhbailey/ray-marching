///  @file TorusNode.cpp
///  @brief Handles logic for Torus node

#include <ngl/Vec2.h>

#include "TorusNode.h"

TorusNode::TorusNode()
{
    m_variableName = "torus0";
    m_materialMap.insert(m_variableName, ngl::Vec3(1.0f, 1.0f, 1.0f));
    QString shaderCode = "float " + m_variableName + " = sdTorus(_p, vec3(0, 0, 0), vec2(2.0, 1.0));\n";
    QString functionCall = " = sdTorus(_p, vec3(0, 0, 0), vec2(2.0, 1.0));\n";

    m_nodeData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_nodeData->setIsSDF(true);
    m_nodeData->setFunctionCall(functionCall);

    m_torusWidget = new TorusNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setWindowTitle("Torus Node");
    m_codeEditor->setPlainText(shaderCode);
    m_codeEditor->setReadOnly(true);
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void TorusNode::createConnections()
{
  connect(m_torusWidget->m_idWidget, SIGNAL(valueChanged(int)), this, SLOT(updateNode()));
  connect(m_torusWidget->m_positionWidget->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->m_positionWidget->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->m_positionWidget->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->getRadiusWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->getRadiusWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->m_inspectCodeButton, SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString TorusNode::caption() const
{
    return QString("Torus");
}

QString TorusNode::name() const
{
    return QString("Torus");
}

std::shared_ptr<NodeData> TorusNode::outData(PortIndex)
{
    return m_nodeData;
}

QWidget* TorusNode::embeddedWidget()
{
    return m_torusWidget;
}

QJsonObject TorusNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_nodeData)
  {
    modelJson["shaderCode"] = m_nodeData->getShaderCode();
    modelJson["variableName"] = m_nodeData->getVariableName();
    modelJson["xPos"] = m_torusWidget->m_positionWidget->getVec3().m_x;
    modelJson["yPos"] = m_torusWidget->m_positionWidget->getVec3().m_y;
    modelJson["zPos"] = m_torusWidget->m_positionWidget->getVec3().m_z;
    modelJson["xRadius"] = m_torusWidget->getRadiusWidget()->getVec2().m_x;
    modelJson["yRadius"] = m_torusWidget->getRadiusWidget()->getVec2().m_y;
    modelJson["id"] = m_torusWidget->m_idWidget->value();
  }

  return modelJson;
}

void TorusNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue xp = _p["xPos"];
  QJsonValue yp = _p["yPos"];
  QJsonValue zp = _p["zPos"];
  QJsonValue xr  = _p["xRadius"];
  QJsonValue yr  = _p["yRadius"];
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
    m_torusWidget->m_positionWidget->setVec3(position);
  }

  if (!xr.isUndefined() && !yr.isUndefined())
  {
    ngl::Vec2 radius = ngl::Vec2(xr.toDouble(), yr.toDouble());
    m_torusWidget->getRadiusWidget()->setVec2(radius);
  }

  if (!id.isUndefined())
  {
    m_torusWidget->m_idWidget->setValue(id.toInt());
  }

  m_nodeData->setIsSDF(true);
}

void TorusNode::updateNode()
{
  // Setup variables
  ngl::Vec3 pos = m_torusWidget->m_positionWidget->getVec3();
  double px = pos.m_x;
  double py = pos.m_y;
  double pz = pos.m_z;

  ngl::Vec2 radiusVec = m_torusWidget->getRadiusWidget()->getVec2();
  double rx = radiusVec.m_x;
  double ry = radiusVec.m_y;

  // Convert to string
  QString position = QString::number(px) + ", " + QString::number(py) + ", " + QString::number(pz);
  QString radius = QString::number(rx) + ", " + QString::number(ry);

  // Update node data
  m_variableName = "torus" + QString::number(m_torusWidget->m_idWidget->value());
  m_nodeData->setVariableName(m_variableName);

  QString shaderCode = "float " + m_variableName + " = sdTorus(_p, vec3(" + position + "), vec2(" + radius + "));\n";
  m_nodeData->setShaderCode(shaderCode);

  QString functionCall = " = sdTorus(_p, vec3(" + position + "), vec2(" + radius + "));\n";
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

void TorusNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}