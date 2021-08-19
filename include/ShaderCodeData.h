/// \brief Stores node data to be transferred to other nodes
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef SHADERCODEDATA_H_
#define SHADERCODEDATA_H_

#include <QString>
#include <QMap>

#include <nodes/NodeData>

#include <ngl/Vec3.h>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class ShaderCodeData : public NodeData
{
public:
  ShaderCodeData() {}

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

  ngl::Vec3 getMaterial() const { return m_material; }
  void setMaterial(ngl::Vec3 _material) { m_material = _material; }

  QMap<QString, ngl::Vec3> getMaterialMap() const { return m_materialMap; }
  void setMaterialMap(QMap<QString, ngl::Vec3> _materialMap) { m_materialMap = _materialMap; }

  bool getIsBooleanOp() const { return m_isBooleanOp; }
  void setIsBooleanOp(bool _bool) { m_isBooleanOp = _bool; }

  bool getIsMaterial() const { return m_isMaterial; }
  void setIsMaterial(bool _bool) { m_isMaterial = _bool; }

  bool getIsSDF() const { return m_isSDF; }
  void setIsSDF(bool _bool) { m_isSDF = _bool; }

private:
  QString m_shaderCode;
  QString m_variableName;
  QString m_functionCall;
  ngl::Vec3 m_material;
  QMap<QString, ngl::Vec3> m_materialMap;

  bool m_isBooleanOp = false;
  bool m_isMaterial = false;
  bool m_isSDF = false;
};

#endif  // _SHADERCODEDATA_H_