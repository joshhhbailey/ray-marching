#pragma once

#include <QString>

#include <nodes/NodeData>

#include <ngl/Vec3.h>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class ShaderCodeData : public NodeData
{
public:
  ShaderCodeData()
  {

  }

  ShaderCodeData(QString const _shaderCode, QString const _variableName, QString const _functionCode)
  {
    m_shaderCode = _shaderCode;
    m_variableName = _variableName;
    m_functionCode = _functionCode;
  }

  NodeDataType type() const override { return NodeDataType {"SDF", "SDF Output"}; }

  QString getShaderCode() const { return m_shaderCode; }
  void setShaderCode(QString const _shaderCode) { m_shaderCode = _shaderCode; }

  QString getVariableName() const { return m_variableName; }
  void setVariableName(QString const _variableName) { m_variableName = _variableName; }

  QString getFunctionCode() const { return m_functionCode; }
  void setFunctionCode(QString const _functionCode) { m_functionCode = _functionCode; }

  QString getShapeA() const { return m_shapeA; }
  void setShapeA(QString const _shapeA) { m_shapeA = _shapeA; }

  QString getShapeB() const { return m_shapeB; }
  void setShapeB(QString const _shapeB) { m_shapeB = _shapeB; }

private:
  QString m_shaderCode;
  QString m_variableName;
  QString m_functionCode;

  // Boolean Operators
  QString m_shapeA;
  QString m_shapeB;
};