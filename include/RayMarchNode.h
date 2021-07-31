#pragma once

#include <QtCore/QObject>

#include <nodes/NodeDataModel>

#include <memory>

#include "ShaderCodeData.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;

class RayMarchNode : public NodeDataModel
{
  Q_OBJECT

public:
  RayMarchNode();
  virtual ~RayMarchNode() {}
  QString caption() const override;
  QString name() const override;
  unsigned int nPorts(PortType _portType) const override;
  NodeDataType dataType(PortType _portType, PortIndex _portIndex) const override;
  void setInData(std::shared_ptr<NodeData> _data, PortIndex _portIndex) override;
  std::shared_ptr<NodeData> outData(PortIndex) override;
  QWidget* embeddedWidget() override;

private:
  QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;

  void codeSetup();

  std::shared_ptr<ShaderCodeData> m_rayMarchData;
  QString m_shaderCode;
  QString m_variableName;
  QString m_functionCode;
  QString m_evaluatedCode;
};
