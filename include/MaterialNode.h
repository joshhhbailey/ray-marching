/// \brief Handles logic for Material node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef MATERIALNODE_H_
#define MATERIALNODE_H_

#include <QtCore/QObject>

#include <NodeDelegateModel>

#include <ngl/Vec3.h>

#include "ShaderCodeData.h"
#include "MaterialNodeWidget.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortType;
using QtNodes::PortIndex;

class MaterialNode : public NodeDelegateModel
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
  ConnectionPolicy portConnectionPolicy(PortType, PortIndex) const override { return ConnectionPolicy::Many; }
  void setInData(std::shared_ptr<NodeData>, PortIndex) override { }
  std::shared_ptr<NodeData> outData(PortIndex port) override;
  QWidget* embeddedWidget() override;
  QJsonObject save() const override;
  void load(QJsonObject const &_p) override;

public slots:
  void updateNode();

private:
  std::shared_ptr<ShaderCodeData> m_materialData;
  MaterialNodeWidget *m_materialWidget;

  ngl::Vec3 m_material;
};

#endif  // _MATERIALNODE_H_