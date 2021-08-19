/// \brief Handles logic for Box node
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef BOXNODE_H_
#define BOXNODE_H_

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
  std::shared_ptr<NodeData> outData(PortIndex port) override;
  QWidget* embeddedWidget() override;
  QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;

public slots:
  void updateNode() override;
  void inspectCodeButtonClicked();

private:
  BoxNodeWidget *m_boxWidget;
};

#endif  // _BOXNODE_H_