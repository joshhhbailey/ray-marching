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

class MyNodeData : public NodeData
{
public:
  NodeDataType type() const
  {
    return NodeDataType {"MyNodeData", "My Node Data"};
  }
};

class SimpleNodeData : public NodeData
{
public:
  NodeDataType type() const
  {
    return NodeDataType {"SimpleData", "Simple Data"};
  }
};

class TestNode : public NodeDataModel
{
  Q_OBJECT

public:
  virtual ~TestNode() {}
  QString caption() const;
  QString name() const;
  unsigned int nPorts(PortType portType) const;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const;
  std::shared_ptr<NodeData> outData(PortIndex port);
  void setInData(std::shared_ptr<NodeData>, int);
  QWidget* embeddedWidget();
};
