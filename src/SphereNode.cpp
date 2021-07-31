#pragma once

#include "SphereNode.h"

#include <QtCore/QJsonValue>

SphereNode::SphereNode()
{
    QString shaderCode =
    "float sdSphere(vec3 _p, vec3 _pos, float _r)\n"
    "{\n"
    "   vec4 sphere = vec4(_pos, _r);\n"
    "   return length(_p - sphere.xyz) - sphere.w;\n"
    "}\n";

    QString variableName = "sphere";

    QString functionCode = "  float " + variableName + " = sdSphere(_p, vec3(0, 1, 6), 1.0);\n";

    m_sphereData = std::make_shared<ShaderCodeData>(shaderCode, variableName, functionCode);
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
    return nullptr;
}

QJsonObject SphereNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_sphereData)
  {
    modelJson["shaderCode"] = m_sphereData->getShaderCode();
    modelJson["variableName"] = m_sphereData->getVariableName();
    modelJson["functionCode"] = m_sphereData->getFunctionCode();
  }

  return modelJson;
}

void SphereNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue fc = _p["functionCode"];

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
}