#include "CylinderNode.h"

#include <ngl/Vec3.h>

#include <iostream>

CylinderNode::CylinderNode()
{
    m_variableName = "cylinder0";
    QString shaderCode = "float " + m_variableName + " = sdCylinder(_p, vec3(0, 0, 0), vec3(0, 0, 0), 1.0);\n";
    QString functionCall = " = sdCylinder(_p, vec3(0, 0, 0), vec3(0, 0, 0), 1.0);\n";

    m_cylinderData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_cylinderData->setFunctionCall(functionCall);

    m_cylinderWidget = new CapsuleNodeWidget();
    m_codeEditor = new CodeEditor();
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

unsigned int CylinderNode::nPorts(PortType _portType) const
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

NodeDataType CylinderNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> CylinderNode::outData(PortIndex)
{
    return m_cylinderData;
}

QWidget* CylinderNode::embeddedWidget()
{
    return m_cylinderWidget;
}

QJsonObject CylinderNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_cylinderData)
  {
    modelJson["shaderCode"] = m_cylinderData->getShaderCode();
    modelJson["variableName"] = m_cylinderData->getVariableName();
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

  m_cylinderData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_cylinderData->setShaderCode(shaderCode);
  }

  if (!vn.isUndefined())
  {
    QString variableName = vn.toString();
    m_cylinderData->setVariableName(variableName);
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
}

void CylinderNode::updateNode()
{
  // Setup variables
  ngl::Vec3 posA = m_cylinderWidget->getPositionAWidget()->getVec3();
  int Ax = posA.m_x;
  int Ay = posA.m_y;
  int Az = posA.m_z;

  ngl::Vec3 posB = m_cylinderWidget->getPositionBWidget()->getVec3();
  int Bx = posB.m_x;
  int By = posB.m_y;
  int Bz = posB.m_z;

  // Convert to string
  QString positionA = QString::number(Ax) + ", " + QString::number(Ay) + ", " + QString::number(Az);
  QString positionB = QString::number(Bx) + ", " + QString::number(By) + ", " + QString::number(Bz);
  QString radius = QString::number(m_cylinderWidget->getRadiusWidget()->value());

  // Update node data
  m_variableName = "capsule" + QString::number(m_cylinderWidget->getIDWidget()->value());
  m_cylinderData->setVariableName(m_variableName);

  QString shaderCode = "float " + m_variableName + " = sdCylinder(_p, vec3(" + positionA + "), vec3(" + positionB + "), " + radius + ");\n";
  m_cylinderData->setShaderCode(shaderCode);

  QString functionCall = " = sdCylinder(_p, vec3(" + positionA + "), vec3(" + positionB + "), " + radius + ");\n";
  m_cylinderData->setFunctionCall(functionCall);

  // Tell connected node to update received data
  Q_EMIT dataUpdated(0);
}

void CylinderNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}