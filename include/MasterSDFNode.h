#pragma once

#include <QtCore/QObject>

#include <nodes/NodeDataModel>
#include <nodes/Connection>

#include "ShaderCodeData.h"
#include "CodeEditor.h"
#include "SyntaxHighlighter.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeValidationState;
using QtNodes::Connection;

class MasterSDFNode : public NodeDataModel
{
public:
  MasterSDFNode() {}
  virtual ~MasterSDFNode() {}
  virtual void updateNode() {}
  
  unsigned int nPorts(PortType _portType) const override;
  NodeDataType dataType(PortType _portType, PortIndex _portIndex) const override;
  bool portCaptionVisible(PortType _portType, PortIndex _portIndex) const override;
  QString portCaption(PortType _portType, PortIndex _portIndex) const override;
  ConnectionPolicy portOutConnectionPolicy(PortIndex) const override { return ConnectionPolicy::One; }
  NodeValidationState validationState() const override;
  QString validationMessage() const override;
  void inputConnectionDeleted(Connection const&) override;
  void setInData(std::shared_ptr<NodeData>, int) override;

  std::shared_ptr<ShaderCodeData> m_nodeData;
  std::shared_ptr<ShaderCodeData> m_receivedNode;

  QString m_variableName;
  QMap<QString, ngl::Vec3> m_materialMap;

  CodeEditor *m_codeEditor;
  SyntaxHighlighter *m_syntaxHighlighter;

  // Validation
  NodeValidationState m_modelValidationState = NodeValidationState::Warning;
  QString m_modelValidationError = QStringLiteral("Missing material!");
};
