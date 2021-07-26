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
  QString caption() const;
  QString name() const;
  unsigned int nPorts(PortType portType) const;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const;
  void setInData(std::shared_ptr<NodeData>, int) {}
  std::shared_ptr<NodeData> outData(PortIndex);
  QWidget* embeddedWidget();

  /*QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;*/
};
