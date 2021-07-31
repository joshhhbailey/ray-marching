#pragma once

#include <QString>

#include <nodes/NodeData>

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

  NodeDataType type() const override
  {
    return NodeDataType {"SDF", "Output"};
  }

  QString getShaderCode() const
  {
    return m_shaderCode;
  }

  void setShaderCode(QString const _shaderCode)
  {
    m_shaderCode = _shaderCode;
  }

  QString getVariableName() const
  {
    return m_variableName;
  }

  void setVariableName(QString const _variableName)
  {
    m_variableName = _variableName;
  }

  QString getFunctionCode() const
  {
    return m_functionCode;
  }

  void setFunctionCode(QString const _functionCode)
  {
    m_functionCode = _functionCode;
  }

private:
  QString m_shaderCode;
  QString m_variableName;
  QString m_functionCode;
};