#pragma once

#include <QtCore/QObject>

#include "MasterSDFNode.h"
#include "CapsuleNodeWidget.h"

class CylinderNode : public MasterSDFNode
{
  Q_OBJECT

public:
  CylinderNode();
  virtual ~CylinderNode() {}
  void createConnections();
  QString caption() const override;
  QString name() const override;
  std::shared_ptr<NodeData> outData(PortIndex port) override;
  QWidget* embeddedWidget() override;
  QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;

public slots:
  void updateNode() override;
  void inspectCodeButtonClicked();

private:
  CapsuleNodeWidget *m_cylinderWidget;
};
