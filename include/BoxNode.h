#pragma once

#include <QtCore/QObject>

#include "MasterSDFNode.h"
#include "BoxNodeWidget.h"

class BoxNode : public MasterSDFNode
{
  Q_OBJECT

public:
  BoxNode();
  virtual ~BoxNode() {}
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
  BoxNodeWidget *m_boxWidget;
};
