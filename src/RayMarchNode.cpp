#pragma once

#include "RayMarchNode.h"

#include <ngl/Vec3.h>

#include <iostream>

RayMarchNode::RayMarchNode()
{
    m_rayMarchData = std::make_shared<ShaderCodeData>();
    m_rayMarchWidget = new RayMarchNodeWidget();

    m_rayOrigin = "0, 0, 0";
    m_lightPosition = "0, 0, 0";

    createConnections();
}

void RayMarchNode::createConnections()
{
  connect(m_rayMarchWidget->getRayOriginWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_rayMarchWidget->getRayOriginWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_rayMarchWidget->getRayOriginWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_rayMarchWidget->getLightPositionWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_rayMarchWidget->getLightPositionWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_rayMarchWidget->getLightPositionWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
}

QString RayMarchNode::caption() const
{
    return QString("Ray March");
}

QString RayMarchNode::name() const
{
    return QString("Ray March");
}

unsigned int RayMarchNode::nPorts(PortType _portType) const
{
    unsigned int result = 1;

    switch (_portType)
    {
        case PortType::In:
        {
            result = 1;
            break;
        }
        case PortType::Out:
        {
            result = 0;
            break;
        }
        case PortType::None:
        {
            break;
        }
    }
    return result;
}

NodeDataType RayMarchNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> RayMarchNode::outData(PortIndex)
{
  return m_rayMarchData;
}


void RayMarchNode::setInData(std::shared_ptr<NodeData> _data, PortIndex _portIndex)
{
  auto receivedNode = std::dynamic_pointer_cast<ShaderCodeData>(_data);

  if (receivedNode)
  {
    // Data received
    if (_portIndex == 0)
    {
      m_shaderCode = receivedNode->getShaderCode();
      m_variableName = receivedNode->getVariableName();
      m_functionCode = receivedNode->getFunctionCode();
      updateCode();

      m_modelValidationState = NodeValidationState::Valid;
    }
  }
}

QWidget* RayMarchNode::embeddedWidget()
{
  return m_rayMarchWidget;
}

NodeValidationState RayMarchNode::validationState() const
{
  return m_modelValidationState;
}

QString RayMarchNode::validationMessage() const
{
  return m_modelValidationError;
}

void RayMarchNode::inputConnectionDeleted(Connection const&)
{
  // Reset node
  m_modelValidationState = NodeValidationState::Error;
  m_rayMarchData = std::make_shared<ShaderCodeData>();
  m_shaderCode = QString();
  m_variableName = QString();
  m_functionCode = QString();
  m_evaluatedCode = QString();
}

QJsonObject RayMarchNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_rayMarchData)
  {
    modelJson["shaderCode"] = m_rayMarchData->getShaderCode();
    modelJson["ROxPos"] = m_rayMarchWidget->getRayOriginWidget()->getVec3().m_x;
    modelJson["ROyPos"] = m_rayMarchWidget->getRayOriginWidget()->getVec3().m_y;
    modelJson["ROzPos"] = m_rayMarchWidget->getRayOriginWidget()->getVec3().m_z;
    modelJson["lightxPos"] = m_rayMarchWidget->getLightPositionWidget()->getVec3().m_x;
    modelJson["lightyPos"] = m_rayMarchWidget->getLightPositionWidget()->getVec3().m_y;
    modelJson["lightzPos"] = m_rayMarchWidget->getLightPositionWidget()->getVec3().m_z;
  }
  return modelJson;
}

void RayMarchNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue ROxp = _p["ROxPos"];
  QJsonValue ROyp = _p["ROyPos"];
  QJsonValue ROzp = _p["ROzPos"];
  QJsonValue lightxp = _p["lightxPos"];
  QJsonValue lightyp = _p["lightyPos"];
  QJsonValue lightzp = _p["lightzPos"];

  m_rayMarchData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_rayMarchData->setShaderCode(shaderCode);
  }

  if (!ROxp.isUndefined() && !ROyp.isUndefined() && !ROzp.isUndefined())
  {
    ngl::Vec3 ROposition = ngl::Vec3(ROxp.toDouble(), ROyp.toDouble(), ROzp.toDouble());
    m_rayMarchWidget->getRayOriginWidget()->setVec3(ROposition);
  }

  if (!lightxp.isUndefined() && !lightyp.isUndefined() && !lightzp.isUndefined())
  {
    ngl::Vec3 lightPosition = ngl::Vec3(lightxp.toDouble(), lightyp.toDouble(), lightzp.toDouble());
    m_rayMarchWidget->getRayOriginWidget()->setVec3(lightPosition);
  }
}

void RayMarchNode::updateCode()
{
  m_evaluatedCode =
    "#define MAX_STEPS 100\n"
    "#define MAX_DISTANCE 100.0\n"
    "#define SURFACE_DISTANCE 0.01\n"
    "\n"
    + m_shaderCode +
    "\n"
    "float GetDistance(vec3 _p)\n"
    "{\n"
    + m_functionCode +
    "\n"
    "   // Return distance of closest scene object\n"
    "   //float closestDistance = min(sphere, plane);\n"
    "\n"
    "   return " + m_variableName + ";\n"
    "}\n"
    "\n"
    "float RayMarch(vec3 _rayOrigin, vec3 _rayDirection)\n"
    "{\n"
    "   float originDistance = 0.0;\n"
    "   for (int i = 0; i < MAX_STEPS; i++)\n"
    "   {\n"
    "       // Marching point\n"
    "       vec3 p = _rayOrigin + (originDistance * _rayDirection);\n"
    "\n"
    "       // Calculate distance from current point (p) to scene object\n"
    "       float sceneDistance = GetDistance(p);\n"
    "       originDistance += sceneDistance;\n"
    "\n"
    "       // Scene has been hit, or surpassed MAX_DISTANCE\n"
    "       if (sceneDistance < SURFACE_DISTANCE || originDistance > MAX_DISTANCE)\n"
    "       {\n"
    "           break;\n"
    "       }\n"
    "   }\n"
    "   return originDistance;\n"
    "}\n"
    "\n"
    "vec3 GetNormal(vec3 _p)\n"
    "{\n"
    "    // Distance from point _p to surface\n"
    "    float surfaceDistance = GetDistance(_p);\n"
    "\n"
    "    // Distance to sample surrounding points\n"
    "    vec2 threshold = vec2(0.01, 0);\n"
    "\n"
    "    // Sample points\n"
    "    vec3 normal = surfaceDistance - vec3(GetDistance(_p - threshold.xyy),\n"
    "                                       GetDistance(_p - threshold.yxy),\n"
    "                                       GetDistance(_p - threshold.yyx));\n"
    "\n"
    "    return normalize(normal);\n"
    "}\n"
    "\n"    
    "float GetLight(vec3 _p)\n"
    "{\n"
    "   // Define light\n"
    "   vec3 lightPosition = vec3(" + m_lightPosition + ");\n"
    "   lightPosition.xz += vec2(sin(iTime), cos(iTime)) * 2;\n"
    "   vec3 lightVector = normalize(lightPosition - _p);\n"
    "\n"
    "   // Calculate normal of intersection point\n"
    "   vec3 normal = GetNormal(_p);\n"
    "\n"
    "   // Clamp diffuse value from -1 to 1, -> 0 to 1\n"
    "   float diffuse = clamp(dot(normal, lightVector), 0.0, 1.0);\n"
    "\n"
    "   // Calculate distance between _p and light source\n"
    "   float lightDistance = RayMarch(_p + (normal * SURFACE_DISTANCE * 2.0), lightVector);\n"
    "\n"
    "   // Hit something\n"
    "   if (lightDistance < length(lightPosition - _p))\n"
    "   {\n"
    "       diffuse *= 0.1;\n"
    "   }\n"
    "\n"
    "   return diffuse;\n"
    "}\n"
    "\n"
    "void main()\n"
    "{\n"
    "   // Normalize pixel coordinates (from -0.5 to 0.5), flip y\n"
    "   vec2 uv = vec2(iUV.x - 0.5, (iUV.y - 0.5) * -1);\n"
    "\n"
    "   // Default black\n"
    "   vec3 colour = vec3(0);\n"
    "\n"
    "   // Camera setup\n"
    "   vec3 rayOrigin = vec3(" + m_rayOrigin + ");\n"
    "   vec3 rayDirection = normalize(vec3(uv.x, uv.y, 1));\n"
    "\n"
    "   // Fire rays, return distance to intersection\n"
    "   float rayDistance = RayMarch(rayOrigin, rayDirection);\n"
    "\n"
    "   // Get point of intersection\n"
    "   vec3 p = rayOrigin + (rayDirection * rayDistance);\n"
    "\n"
    "   // Calculate lighting and shadows\n"
    "   float diffuse = GetLight(p);\n"
    "   colour = vec3(diffuse);\n"
    "\n"
    "   fragColour = vec4(colour, 1.0);\n"
    "}\n";

    m_rayMarchData->setShaderCode(m_evaluatedCode);
}

void RayMarchNode::updateNode()
{
  // Setup variables
  ngl::Vec3 ROpos = m_rayMarchWidget->getRayOriginWidget()->getVec3();
  int ROx = ROpos.m_x;
  int ROy = ROpos.m_y;
  int ROz = ROpos.m_z;

  ngl::Vec3 lightPos = m_rayMarchWidget->getLightPositionWidget()->getVec3();
  int lightx = lightPos.m_x;
  int lighty = lightPos.m_y;
  int lightz = lightPos.m_z;

  // Convert to string
  QString ROposition = QString::number(ROx) + ", " + QString::number(ROy) + ", " + QString::number(ROz);
  QString lightPosition = QString::number(lightx) + ", " + QString::number(lighty) + ", " + QString::number(lightz);

  // Update
  m_rayOrigin = ROposition;
  m_lightPosition = lightPosition;

  updateCode();
}