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

  ShaderCodeData(QString const _shaderCode, QString const _variableName)
  {
    m_shaderCode = _shaderCode;
    m_variableName = _variableName;
  }

  NodeDataType type() const override { return NodeDataType {"SDF", "SDF Output"}; }

  QString getShaderCode() const { return m_shaderCode; }
  void setShaderCode(QString const _shaderCode) { m_shaderCode = _shaderCode; }

  QString getVariableName() const { return m_variableName; }
  void setVariableName(QString const _variableName) { m_variableName = _variableName; }

  QString getFunctionCall() const { return m_functionCall; }
  void setFunctionCall(QString const _functionCall) { m_functionCall = _functionCall; }

  bool getBooleanOp() const { return m_isBooleanOp; }
  void setBooleanOp(bool _bool) { m_isBooleanOp = _bool; }

  QString getShapeA() const { return m_shapeA; }
  void setShapeA(QString const _shapeA) { m_shapeA = _shapeA; }

  QString getShapeB() const { return m_shapeB; }
  void setShapeB(QString const _shapeB) { m_shapeB = _shapeB; }

  int getIteration() { return m_iteration; }
  void setIteration(int _iteration) { m_iteration = _iteration; };
  void addIteration() { m_iteration++; }

private:
  QString m_shaderCode;
  QString m_variableName;
  QString m_functionCall;

  // Boolean Operators
  bool m_isBooleanOp = false;
  QString m_shapeA;
  QString m_shapeB;
  int m_iteration = 0;
};