/// \brief Handles logic for all SDF nodes
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef MASTERSDFNODE_H_
#define MASTERSDFNODE_H_

#include <QtCore/QObject>

#include <NodeDelegateModel>
#include <NodeState>

#include <ngl/Vec3.h>

#include "ShaderCodeData.h"
#include "CodeEditor.h"
#include "SyntaxHighlighter.h"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeState;
using QtNodes::ConnectionId;
using QtNodes::ConnectionPolicy;

class MasterSDFNode : public NodeDelegateModel
{
public:
  MasterSDFNode() {}
  virtual ~MasterSDFNode() {}
  virtual void updateNode() {}
  
  unsigned int nPorts(PortType _portType) const override;
  NodeDataType dataType(PortType _portType, PortIndex _portIndex) const override;
  bool portCaptionVisible(PortType _portType, PortIndex _portIndex) const override;
  QString portCaption(PortType _portType, PortIndex _portIndex) const override;
  ConnectionPolicy portConnectionPolicy(PortType, PortIndex) const override { return ConnectionPolicy::One; }
  //NodeState validationState() const override;
  //QString validationMessage() const override;
  void inputConnectionDeleted(ConnectionId const&) override;
  void setInData(std::shared_ptr<NodeData>, PortIndex) override;

  std::shared_ptr<ShaderCodeData> m_nodeData;
  std::shared_ptr<ShaderCodeData> m_receivedNode;

  QString m_variableName;
  QMap<QString, ngl::Vec3> m_materialMap;

  CodeEditor *m_codeEditor;
  SyntaxHighlighter *m_syntaxHighlighter;

  // Validation
  //NodeState m_modelValidationState = NodeState::Warning;
  QString m_modelValidationError = QStringLiteral("Missing material!");
};

#endif  // _MASTERSDFNODE_H_