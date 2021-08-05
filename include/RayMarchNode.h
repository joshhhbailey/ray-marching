#pragma once

#include <QtCore/QObject>

#include <nodes/NodeDataModel>

#include "ShaderCodeData.h"
#include "RayMarchNodeWidget.h"
#include "CodeEditor.h"
#include "SyntaxHighlighter.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeValidationState;
using QtNodes::Connection;

class RayMarchNode : public NodeDataModel
{
  Q_OBJECT

public:
  RayMarchNode();
  virtual ~RayMarchNode() {}
  void createConnections();
  QString caption() const override;
  QString name() const override;
  unsigned int nPorts(PortType _portType) const override;
  bool portCaptionVisible(PortType _portType, PortIndex _portIndex) const override;
  QString portCaption(PortType _portType, PortIndex _portIndex) const override;
  NodeDataType dataType(PortType _portType, PortIndex _portIndex) const override;
  void setInData(std::shared_ptr<NodeData> _data, PortIndex _portIndex) override;
  std::shared_ptr<NodeData> outData(PortIndex) override;
  QWidget* embeddedWidget() override;
  QJsonObject save() const override;
  void restore(QJsonObject const &_p) override;
  NodeValidationState validationState() const override;
  QString validationMessage() const override;
  void inputConnectionDeleted(Connection const&) override;

public slots:
  void updateNode();
  void inspectCodeButtonClicked();

private:
  void updateCode();

  // Validation
  NodeValidationState m_modelValidationState = NodeValidationState::Error;
  QString m_modelValidationError = QStringLiteral("Missing inputs!");

  std::shared_ptr<ShaderCodeData> m_rayMarchData;
  RayMarchNodeWidget *m_rayMarchWidget;

  CodeEditor *m_codeEditor;
  SyntaxHighlighter *m_syntaxHighlighter;

  QString m_shaderCode;
  QString m_variableName;
  QString m_functionCode;
  QString m_evaluatedCode;

  QString m_rayOrigin;
  QString m_lightPosition;
};
