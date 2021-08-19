/// \brief Handles logic for Plane node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef PLANENODE_H_
#define PLANENODE_H_

#include <QtCore/QObject>

#include "MasterSDFNode.h"
#include "PlaneNodeWidget.h"

class PlaneNode : public MasterSDFNode
{
  Q_OBJECT

public:
  PlaneNode();
  virtual ~PlaneNode() {}
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
  PlaneNodeWidget *m_planeWidget;
};

#endif  // _PLANENODE_H_