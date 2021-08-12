#pragma once

#include <QtCore/QObject>

#include "MasterSDFNode.h"
#include "CapsuleNodeWidget.h"

class CapsuleNode : public MasterSDFNode
{
  Q_OBJECT

public:
  CapsuleNode();
  virtual ~CapsuleNode() {}
  void createConnections();
  QString caption() const override;
  QString name() const override;
  void setInData(std::shared_ptr<NodeData>, int) override;
  std::shared_ptr<NodeData> outData(PortIndex port) override;
  QWidget* embeddedWidget() override;
  QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;
  void inputConnectionDeleted(Connection const&) override;

public slots:
  void updateNode();
  void inspectCodeButtonClicked();

private:
  CapsuleNodeWidget *m_capsuleWidget;
};
