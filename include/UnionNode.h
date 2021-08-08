#pragma once

#include <QtCore/QObject>

#include <nodes/NodeDataModel>
#include <nodes/Connection>

#include "ShaderCodeData.h"
#include "UnionNodeWidget.h"
#include "CodeEditor.h"
#include "SyntaxHighlighter.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeValidationState;
using QtNodes::Connection;

class UnionNode : public NodeDataModel
{
  Q_OBJECT

public:
  UnionNode();
  virtual ~UnionNode() {}
  void createConnections();
  QString caption() const override;
  QString name() const override;
  unsigned int nPorts(PortType _portType) const override;
  bool portCaptionVisible(PortType _portType, PortIndex _portIndex) const override;
  QString portCaption(PortType _portType, PortIndex _portIndex) const override;
  NodeDataType dataType(PortType _portType, PortIndex _portIndex) const override;
  void setInData(std::shared_ptr<NodeData>, int) override;
  std::shared_ptr<NodeData> outData(PortIndex _port) override;
  QWidget* embeddedWidget() override;
  QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;
  NodeValidationState validationState() const override;
  QString validationMessage() const override;
  void inputConnectionDeleted(Connection const&_connection) override;

public slots:
  void inspectCodeButtonClicked();

private:
  void updateCode();

  // Validation
  NodeValidationState m_modelValidationState = NodeValidationState::Error;
  QString m_modelValidationError = QStringLiteral("Missing inputs!");

  std::shared_ptr<ShaderCodeData> m_unionData;
  UnionNodeWidget *m_unionWidget;

  CodeEditor *m_codeEditor;
  SyntaxHighlighter *m_syntaxHighlighter;

  std::shared_ptr<ShaderCodeData> m_receivedNodeA;
  std::shared_ptr<ShaderCodeData> m_receivedNodeB;

  QString m_shaderCode;
  QString m_shapeA = "/*Missing code!*/";
  QString m_shapeAShaderCode = "/*Missing code!*/\n";
  QString m_shapeAfunctionCall = "/*Missing code!*/";
  bool m_shapeAisBoolean = false;
  QString m_shapeB = "/*Missing code!*/";
  QString m_shapeBShaderCode = "/*Missing code!*/\n";
  QString m_shapeBfunctionCall = "/*Missing code!*/";
  bool m_shapeBisBoolean = false;
};
