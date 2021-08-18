#pragma once

#include <QtCore/QObject>

#include <nodes/NodeDataModel>

#include <ngl/Vec3.h>

#include "ShaderCodeData.h"
#include "MaterialNodeWidget.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;

class MaterialNode : public NodeDataModel
{
  Q_OBJECT

public:
  MaterialNode();
  virtual ~MaterialNode() {}
  void createConnections();
  QString caption() const override;
  QString name() const override;
  unsigned int nPorts(PortType portType) const override;
  bool portCaptionVisible(PortType _portType, PortIndex _portIndex) const override;
  QString portCaption(PortType _portType, PortIndex _portIndex) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  ConnectionPolicy portOutConnectionPolicy(PortIndex) const override { return ConnectionPolicy::Many; }
  void setInData(std::shared_ptr<NodeData>, int) override { }
  std::shared_ptr<NodeData> outData(PortIndex port) override;
  QWidget* embeddedWidget() override;
  QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;

public slots:
  void updateNode();

private:
  std::shared_ptr<ShaderCodeData> m_materialData;
  MaterialNodeWidget *m_materialWidget;

  ngl::Vec3 m_material;
};
