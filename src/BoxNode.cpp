///  @file BoxNode.cpp
///  @brief Handles logic for Box node

#include "BoxNode.h"

BoxNode::BoxNode()
{
    m_variableName = "box0";
    m_materialMap.insert(m_variableName, ngl::Vec3(1.0f, 1.0f, 1.0f));
    QString shaderCode = "float " + m_variableName + " = sdBox(_p, vec3(0, 0, 0), vec3(1, 1, 1));\n";
    QString functionCall = " = sdBox(_p, vec3(0, 0, 0), vec3(1, 1, 1));\n";

    m_nodeData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_nodeData->setIsSDF(true);
    m_nodeData->setFunctionCall(functionCall);

    m_boxWidget = new BoxNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setWindowTitle("Box Node");
    m_codeEditor->setPlainText(shaderCode);
    m_codeEditor->setReadOnly(true);
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void BoxNode::createConnections()
{
  connect(m_boxWidget->m_idWidget, SIGNAL(valueChanged(int)), this, SLOT(updateNode()));
  connect(m_boxWidget->m_positionWidget->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->m_positionWidget->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->m_positionWidget->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->getSizeWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->getSizeWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->getSizeWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->m_inspectCodeButton, SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString BoxNode::caption() const
{
    return QString("Box");
}

QString BoxNode::name() const
{
    return QString("Box");
}

std::shared_ptr<NodeData> BoxNode::outData(PortIndex)
{
    return m_nodeData;
}

QWidget* BoxNode::embeddedWidget()
{
    return m_boxWidget;
}

QJsonObject BoxNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_nodeData)
  {
    modelJson["shaderCode"] = m_nodeData->getShaderCode();
    modelJson["variableName"] = m_nodeData->getVariableName();
    modelJson["xPos"] = m_boxWidget->m_positionWidget->getVec3().m_x;
    modelJson["yPos"] = m_boxWidget->m_positionWidget->getVec3().m_y;
    modelJson["zPos"] = m_boxWidget->m_positionWidget->getVec3().m_z;
    modelJson["xSize"] = m_boxWidget->getSizeWidget()->getVec3().m_x;
    modelJson["ySize"] = m_boxWidget->getSizeWidget()->getVec3().m_y;
    modelJson["zSize"] = m_boxWidget->getSizeWidget()->getVec3().m_z;
    modelJson["id"] = m_boxWidget->m_idWidget->value();
  }

  return modelJson;
}

void BoxNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue xp = _p["xPos"];
  QJsonValue yp = _p["yPos"];
  QJsonValue zp = _p["zPos"];
  QJsonValue xs  = _p["xSize"];
  QJsonValue ys  = _p["ySize"];
  QJsonValue zs  = _p["zSize"];
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
    m_boxWidget->m_positionWidget->setVec3(position);
  }

  if (!xs.isUndefined() && !ys.isUndefined() && !zs.isUndefined())
  {
    ngl::Vec3 size = ngl::Vec3(xs.toDouble(), ys.toDouble(), zs.toDouble());
    m_boxWidget->getSizeWidget()->setVec3(size);
  }

  if (!id.isUndefined())
  {
    m_boxWidget->m_idWidget->setValue(id.toInt());
  }

  m_nodeData->setIsSDF(true);
}

void BoxNode::updateNode()
{
  // Setup variables
  ngl::Vec3 pos = m_boxWidget->m_positionWidget->getVec3();
  double px = pos.m_x;
  double py = pos.m_y;
  double pz = pos.m_z;

  ngl::Vec3 sizeVec = m_boxWidget->getSizeWidget()->getVec3();
  double sx = sizeVec.m_x;
  double sy = sizeVec.m_y;
  double sz = sizeVec.m_z;

  // Convert to string
  QString position = QString::number(px) + ", " + QString::number(py) + ", " + QString::number(pz);
  QString size = QString::number(sx) + ", " + QString::number(sy) + ", " + QString::number(sz);

  // Update node data
  m_variableName = "box" + QString::number(m_boxWidget->m_idWidget->value());
  m_nodeData->setVariableName(m_variableName);

  QString shaderCode = "float " + m_variableName + " = sdBox(_p, vec3(" + position + "), vec3(" + size + "));\n";
  m_nodeData->setShaderCode(shaderCode);

  QString functionCall = " = sdBox(_p, vec3(" + position + "), vec3(" + size + "));\n";
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

void BoxNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}