#pragma once

#include <QtCore/QObject>

#include <nodes/NodeData>
#include <nodes/NodeDataModel>

#include <memory>

#include <QtWidgets/QPushButton>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;

class RayMarchData : public NodeData
{
public:
  NodeDataType type() const
  {
    return NodeDataType {"SDF", "Input"};
  }
};

class RayMarchNode : public NodeDataModel
{
  Q_OBJECT

public:
  RayMarchNode();
  virtual ~RayMarchNode() {}
  QString caption() const;
  QString name() const;
  unsigned int nPorts(PortType portType) const;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const;
  void setInData(std::shared_ptr<NodeData>, int);
  std::shared_ptr<NodeData> outData(PortIndex);
  QWidget* embeddedWidget();

  QPushButton *m_compileButton;

public slots:
  void compileButtonClicked();

private:
  void createWidgets();
  void createConnections();

  /*QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;*/
};
