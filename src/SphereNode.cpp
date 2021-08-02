#include "SphereNode.h"

#include <QtCore/QJsonValue>
#include <ngl/Vec3.h>

#include <iostream>

SphereNode::SphereNode()
{
    QString shaderCode =
    "float sdSphere(vec3 _p, vec3 _pos, float _r)\n"
    "{\n"
    "   vec4 sphere = vec4(_pos, _r);\n"
    "   return length(_p - sphere.xyz) - sphere.w;\n"
    "}\n";

    QString variableName = "sphere";

    QString functionCode = "  float " + variableName + " = sdSphere(_p, vec3(0, 0, 0), 1.0);\n";

    m_sphereData = std::make_shared<ShaderCodeData>(shaderCode, variableName, functionCode);
    m_sphereWidget = new SphereNodeWidget();

    createConnections();
}

void SphereNode::createConnections()
{
  connect(m_sphereWidget->getPositionWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updatePosition()));
  connect(m_sphereWidget->getPositionWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updatePosition()));
  connect(m_sphereWidget->getPositionWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updatePosition()));
}

QString SphereNode::caption() const
{
    return QString("Sphere");
}

QString SphereNode::name() const
{
    return QString("Sphere");
}

unsigned int SphereNode::nPorts(PortType _portType) const
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

NodeDataType SphereNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> SphereNode::outData(PortIndex)
{
    return m_sphereData;
}

QWidget* SphereNode::embeddedWidget()
{
    return m_sphereWidget;
}

QJsonObject SphereNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_sphereData)
  {
    modelJson["shaderCode"] = m_sphereData->getShaderCode();
    modelJson["variableName"] = m_sphereData->getVariableName();
    modelJson["functionCode"] = m_sphereData->getFunctionCode();
    modelJson["xPos"] = m_sphereData->getPosition().m_x;
    modelJson["yPos"] = m_sphereData->getPosition().m_y;
    modelJson["zPos"] = m_sphereData->getPosition().m_z;
  }

  return modelJson;
}

void SphereNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue fc = _p["functionCode"];
  QJsonValue xp = _p["xPos"];
  QJsonValue yp = _p["yPos"];
  QJsonValue zp = _p["zPos"];

  m_sphereData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_sphereData->setShaderCode(shaderCode);
  }

  if (!vn.isUndefined())
  {
    QString variableName = vn.toString();
    m_sphereData->setVariableName(variableName);
  }

  if (!fc.isUndefined())
  {
    QString functionCode = fc.toString();
    m_sphereData->setFunctionCode(functionCode);
  }

  if (!xp.isUndefined() && !yp.isUndefined() && !zp.isUndefined())
  {
    ngl::Vec3 position = ngl::Vec3(xp.toDouble(), yp.toDouble(), zp.toDouble());
    m_sphereData->setPosition(position);
    m_sphereWidget->getPositionWidget()->setVec3(position);
  }
}

void SphereNode::updatePosition()
{
  // Set new position
  m_sphereData->setPosition(m_sphereWidget->getPositionWidget()->getVec3());

  // Setup variables
  ngl::Vec3 position = m_sphereData->getPosition();
  int x = position.m_x;
  int y = position.m_y;
  int z = position.m_z;

  // Convert to string
  QString str = QString::number(x) + ", " + QString::number(y) + ", " + QString::number(z);

  // Update function code
  QString functionCode = "  float sphere = sdSphere(_p, vec3(" + str + "), 1.0);\n";
  m_sphereData->setFunctionCode(functionCode);

  // Tell connected node to update received data
  Q_EMIT dataUpdated(0);
}