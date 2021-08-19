/// \brief Handles logic for Torus node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef TORUSNODE_H_
#define TORUSNODE_H_

#include <QtCore/QObject>

#include "MasterSDFNode.h"
#include "TorusNodeWidget.h"

class TorusNode : public MasterSDFNode
{
  Q_OBJECT

public:
  TorusNode();
  virtual ~TorusNode() {}
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
  TorusNodeWidget *m_torusWidget;
};

#endif  // _TORUSNODE_H_