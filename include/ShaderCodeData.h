#pragma once

#include <QString>
#include <QMap>

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

  QMap<QString, ngl::Vec3> getMaterials() const { return m_materials; }
  void setMaterials(QMap<QString, ngl::Vec3> _materials) { m_materials = _materials; }

private:
  QString m_shaderCode;
  QString m_variableName;
  QString m_functionCall;
  QMap<QString, ngl::Vec3> m_materials;

  // Boolean Operators
  bool m_isBooleanOp = false;
};