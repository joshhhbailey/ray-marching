#pragma once

#include <QtCore/QObject>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <memory>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;

class SphereData : public NodeData
{
public:
  NodeDataType type() const
  {
    return NodeDataType {"SDF", "Output"};
  }
};

class SphereNode : public NodeDataModel
{
  Q_OBJECT

public:
  virtual ~SphereNode() {}
  QString caption() const override;
  QString name() const override;
  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  void setInData(std::shared_ptr<NodeData>, int) override;
  std::shared_ptr<NodeData> outData(PortIndex) override;
  QWidget* embeddedWidget() override;

  QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;
};
