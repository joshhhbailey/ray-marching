/// \brief Handles logic for Sphere node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef SPHERENODE_H_
#define SPHERENODE_H_

#include <QtCore/QObject>

#include <ngl/Vec3.h>

#include "MasterSDFNode.h"
#include "SphereNodeWidget.h"

class SphereNode : public MasterSDFNode
{
  Q_OBJECT

public:
  SphereNode();
  virtual ~SphereNode() {}
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
  SphereNodeWidget *m_sphereWidget;
};

#endif  // _SPHERENODE_H_