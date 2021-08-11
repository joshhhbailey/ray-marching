#include "CapsuleNode.h"

#include <ngl/Vec3.h>

#include <iostream>

CapsuleNode::CapsuleNode()
{
    m_variableName = "capsule0";
    QString shaderCode = "float " + m_variableName + " = sdCapsule(_p, vec3(0, 0, 0), vec3(0, 0, 0), 1.0);\n";
    QString functionCall = " = sdCapsule(_p, vec3(0, 0, 0), vec3(0, 0, 0), 1.0);\n";

    m_capsuleData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_capsuleData->setFunctionCall(functionCall);

    m_capsuleWidget = new CapsuleNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setPlainText(shaderCode);
    m_codeEditor->setReadOnly(true);
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void CapsuleNode::createConnections()
{
  connect(m_capsuleWidget->getIDWidget(), SIGNAL(valueChanged(int)), this, SLOT(updateNode()));
  connect(m_capsuleWidget->getPositionAWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_capsuleWidget->getPositionAWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_capsuleWidget->getPositionAWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_capsuleWidget->getPositionBWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_capsuleWidget->getPositionBWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_capsuleWidget->getPositionBWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_capsuleWidget->getRadiusWidget(), SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_capsuleWidget->getInspectCodeButton(), SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString CapsuleNode::caption() const
{
    return QString("Capsule");
}

QString CapsuleNode::name() const
{
    return QString("Capsule");
}

unsigned int CapsuleNode::nPorts(PortType _portType) const
{
    unsigned int result = 1;

    switch (_portType)
    {
        case PortType::In:
        {
            result = 0;
            break;
        }
        case PortType::Out:
        {
            result = 1;
            break;
        }
        case PortType::None:
        {
            break;
        }
    }
    return result;
}

NodeDataType CapsuleNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> CapsuleNode::outData(PortIndex)
{
    return m_capsuleData;
}

QWidget* CapsuleNode::embeddedWidget()
{
    return m_capsuleWidget;
}

QJsonObject CapsuleNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_capsuleData)
  {
    modelJson["shaderCode"] = m_capsuleData->getShaderCode();
    modelJson["variableName"] = m_capsuleData->getVariableName();
    modelJson["AxPos"] = m_capsuleWidget->getPositionAWidget()->getVec3().m_x;
    modelJson["AyPos"] = m_capsuleWidget->getPositionAWidget()->getVec3().m_y;
    modelJson["AzPos"] = m_capsuleWidget->getPositionAWidget()->getVec3().m_z;
    modelJson["BxPos"] = m_capsuleWidget->getPositionBWidget()->getVec3().m_x;
    modelJson["ByPos"] = m_capsuleWidget->getPositionBWidget()->getVec3().m_y;
    modelJson["BzPos"] = m_capsuleWidget->getPositionBWidget()->getVec3().m_z;
    modelJson["radius"] = m_capsuleWidget->getRadiusWidget()->value();
    modelJson["id"] = m_capsuleWidget->getIDWidget()->value();
  }

  return modelJson;
}

void CapsuleNode::restore(QJsonObject const &_p)
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

  m_capsuleData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_capsuleData->setShaderCode(shaderCode);
  }

  if (!vn.isUndefined())
  {
    QString variableName = vn.toString();
    m_capsuleData->setVariableName(variableName);
  }

  if (!Axp.isUndefined() && !Ayp.isUndefined() && !Azp.isUndefined())
  {
    ngl::Vec3 positionA = ngl::Vec3(Axp.toDouble(), Ayp.toDouble(), Azp.toDouble());
    m_capsuleWidget->getPositionAWidget()->setVec3(positionA);
  }

  if (!Bxp.isUndefined() && !Byp.isUndefined() && !Bzp.isUndefined())
  {
    ngl::Vec3 positionB = ngl::Vec3(Bxp.toDouble(), Byp.toDouble(), Bzp.toDouble());
    m_capsuleWidget->getPositionBWidget()->setVec3(positionB);
  }

  if (!r.isUndefined())
  {
    m_capsuleWidget->getRadiusWidget()->setValue(r.toDouble());
  }

  if (!id.isUndefined())
  {
    m_capsuleWidget->getIDWidget()->setValue(id.toInt());
  }
}

void CapsuleNode::updateNode()
{
  // Setup variables
  ngl::Vec3 posA = m_capsuleWidget->getPositionAWidget()->getVec3();
  int Ax = posA.m_x;
  int Ay = posA.m_y;
  int Az = posA.m_z;

  ngl::Vec3 posB = m_capsuleWidget->getPositionBWidget()->getVec3();
  int Bx = posB.m_x;
  int By = posB.m_y;
  int Bz = posB.m_z;

  // Convert to string
  QString positionA = QString::number(Ax) + ", " + QString::number(Ay) + ", " + QString::number(Az);
  QString positionB = QString::number(Bx) + ", " + QString::number(By) + ", " + QString::number(Bz);
  QString radius = QString::number(m_capsuleWidget->getRadiusWidget()->value());

  // Update node data
  m_variableName = "capsule" + QString::number(m_capsuleWidget->getIDWidget()->value());
  m_capsuleData->setVariableName(m_variableName);

  QString shaderCode = "float " + m_variableName + " = sdCapsule(_p, vec3(" + positionA + "), vec3(" + positionB + "), " + radius + ");\n";
  m_capsuleData->setShaderCode(shaderCode);

  QString functionCall = " = sdCapsule(_p, vec3(" + positionA + "), vec3(" + positionB + "), " + radius + ");\n";
  m_capsuleData->setFunctionCall(functionCall);

  // Tell connected node to update received data
  Q_EMIT dataUpdated(0);
}

void CapsuleNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}