///  @file CylinderNode.cpp
///  @brief Handles logic for Cylinder node

#include "CylinderNode.h"

CylinderNode::CylinderNode()
{
    m_variableName = "cylinder0";
    m_materialMap.insert(m_variableName, ngl::Vec3(1.0f, 1.0f, 1.0f));
    QString shaderCode = "float " + m_variableName + " = sdCylinder(_p, vec3(0, 0, 0), vec3(0, 0, 0), 1.0);\n";
    QString functionCall = " = sdCylinder(_p, vec3(0, 0, 0), vec3(0, 0, 0), 1.0);\n";

    m_nodeData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_nodeData->setIsSDF(true);
    m_nodeData->setFunctionCall(functionCall);

    m_cylinderWidget = new CapsuleNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setWindowTitle("Cylinder Node");
    m_codeEditor->setPlainText(shaderCode);
    m_codeEditor->setReadOnly(true);
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void CylinderNode::createConnections()
{
  connect(m_cylinderWidget->getIDWidget(), SIGNAL(valueChanged(int)), this, SLOT(updateNode()));
  connect(m_cylinderWidget->getPositionAWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_cylinderWidget->getPositionAWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_cylinderWidget->getPositionAWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_cylinderWidget->getPositionBWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_cylinderWidget->getPositionBWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_cylinderWidget->getPositionBWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_cylinderWidget->getRadiusWidget(), SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_cylinderWidget->getInspectCodeButton(), SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString CylinderNode::caption() const
{
    return QString("Cylinder");
}

QString CylinderNode::name() const
{
    return QString("Cylinder");
}

std::shared_ptr<NodeData> CylinderNode::outData(PortIndex)
{
    return m_nodeData;
}

QWidget* CylinderNode::embeddedWidget()
{
    return m_cylinderWidget;
}

QJsonObject CylinderNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_nodeData)
  {
    modelJson["shaderCode"] = m_nodeData->getShaderCode();
    modelJson["variableName"] = m_nodeData->getVariableName();
    modelJson["AxPos"] = m_cylinderWidget->getPositionAWidget()->getVec3().m_x;
    modelJson["AyPos"] = m_cylinderWidget->getPositionAWidget()->getVec3().m_y;
    modelJson["AzPos"] = m_cylinderWidget->getPositionAWidget()->getVec3().m_z;
    modelJson["BxPos"] = m_cylinderWidget->getPositionBWidget()->getVec3().m_x;
    modelJson["ByPos"] = m_cylinderWidget->getPositionBWidget()->getVec3().m_y;
    modelJson["BzPos"] = m_cylinderWidget->getPositionBWidget()->getVec3().m_z;
    modelJson["radius"] = m_cylinderWidget->getRadiusWidget()->value();
    modelJson["id"] = m_cylinderWidget->getIDWidget()->value();
  }

  return modelJson;
}

void CylinderNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue Axp = _p["AxPos"];
  QJsonValue Ayp = _p["AyPos"];
  QJsonValue Azp = _p["AzPos"];
  QJsonValue Bxp = _p["BxPos"];
  QJsonValue Byp = _p["ByPos"];
  QJsonValue Bzp = _p["BzPos"];
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

  if (!Axp.isUndefined() && !Ayp.isUndefined() && !Azp.isUndefined())
  {
    ngl::Vec3 positionA = ngl::Vec3(Axp.toDouble(), Ayp.toDouble(), Azp.toDouble());
    m_cylinderWidget->getPositionAWidget()->setVec3(positionA);
  }

  if (!Bxp.isUndefined() && !Byp.isUndefined() && !Bzp.isUndefined())
  {
    ngl::Vec3 positionB = ngl::Vec3(Bxp.toDouble(), Byp.toDouble(), Bzp.toDouble());
    m_cylinderWidget->getPositionBWidget()->setVec3(positionB);
  }

  if (!r.isUndefined())
  {
    m_cylinderWidget->getRadiusWidget()->setValue(r.toDouble());
  }

  if (!id.isUndefined())
  {
    m_cylinderWidget->getIDWidget()->setValue(id.toInt());
  }

  m_nodeData->setIsSDF(true);
}

void CylinderNode::updateNode()
{
  // Setup variables
  ngl::Vec3 posA = m_cylinderWidget->getPositionAWidget()->getVec3();
  double Ax = posA.m_x;
  double Ay = posA.m_y;
  double Az = posA.m_z;

  ngl::Vec3 posB = m_cylinderWidget->getPositionBWidget()->getVec3();
  double Bx = posB.m_x;
  double By = posB.m_y;
  double Bz = posB.m_z;

  // Convert to string
  QString positionA = QString::number(Ax) + ", " + QString::number(Ay) + ", " + QString::number(Az);
  QString positionB = QString::number(Bx) + ", " + QString::number(By) + ", " + QString::number(Bz);
  QString radius = QString::number(m_cylinderWidget->getRadiusWidget()->value());

  // Update node data
  m_variableName = "capsule" + QString::number(m_cylinderWidget->getIDWidget()->value());
  m_nodeData->setVariableName(m_variableName);

  QString shaderCode = "float " + m_variableName + " = sdCylinder(_p, vec3(" + positionA + "), vec3(" + positionB + "), " + radius + ");\n";
  m_nodeData->setShaderCode(shaderCode);

  QString functionCall = " = sdCylinder(_p, vec3(" + positionA + "), vec3(" + positionB + "), " + radius + ");\n";
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

void CylinderNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}