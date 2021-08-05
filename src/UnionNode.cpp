#include "UnionNode.h"

#include <ngl/Vec3.h>

#include <iostream>

UnionNode::UnionNode()
{
    m_unionData = std::make_shared<ShaderCodeData>();
    
    m_unionWidget = new UnionNodeWidget;
    m_codeEditor = new CodeEditor();
    updateCode();
    m_codeEditor->setReadOnly(true);
    m_codeEditor->hide();
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void UnionNode::createConnections()
{
  connect(m_unionWidget->getInspectCodeButton(), SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString UnionNode::caption() const
{
    return QString("Union");
}

QString UnionNode::name() const
{
    return QString("Union");
}

unsigned int UnionNode::nPorts(PortType _portType) const
{
    unsigned int result = 1;

    switch (_portType)
    {
        case PortType::In:
        {
            result = 2;
            break;
        }
        case PortType::Out:
        {
            result = 1;
            break;
        }
        case PortType::None:
        {
            break;
        }
    }
    return result;
}

bool UnionNode::portCaptionVisible(PortType _portType, PortIndex _portIndex) const
{
    Q_UNUSED(_portType);
    Q_UNUSED(_portIndex);
    return true;
}

QString UnionNode::portCaption(PortType _portType, PortIndex _portIndex) const
{
    switch (_portType)
    {
        case PortType::In:
        {
            if (_portIndex == 0)
            {
                return QStringLiteral("SDF A");
            }
            else if (_portIndex == 1)
            {
                return QStringLiteral("SDF B");
            }
            break;
        }

        case PortType::Out:
        {
            return QStringLiteral("SDF Output");
        }

        default:
        {
            break;
        }
    }
    return QString();
}

NodeDataType UnionNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> UnionNode::outData(PortIndex)
{
    return m_unionData;
}

void UnionNode::setInData(std::shared_ptr<NodeData> _data, PortIndex _portIndex)
{
    // Data received
    if (_portIndex == 0)
    {
        auto receivedNodeA = std::dynamic_pointer_cast<ShaderCodeData>(_data);
        if (receivedNodeA)
        {
            m_shapeA = receivedNodeA->getVariableName();
            m_shapeAFunctionCode = receivedNodeA->getFunctionCode();
            m_shapeAShaderCode = receivedNodeA->getShaderCode();
        }
    }

    if (_portIndex == 1)
    {
        auto receivedNodeB = std::dynamic_pointer_cast<ShaderCodeData>(_data);
        if (receivedNodeB)
        {
            m_shapeB = receivedNodeB->getVariableName();
            m_shapeBFunctionCode = receivedNodeB->getFunctionCode();
            m_shapeBShaderCode = receivedNodeB->getShaderCode();
        }
    }
    updateCode();
}

QWidget* UnionNode::embeddedWidget()
{
    return m_unionWidget;
}

void UnionNode::inputConnectionDeleted(Connection const&_connection)
{
  if (_connection.getPortIndex(PortType::In) == 0)
  {
      m_shapeA = "*Missing code!*";
      m_shapeAFunctionCode = "*Missing code!*";
      m_shapeAShaderCode = "*Missing code!*\n";
  }
  if (_connection.getPortIndex(PortType::In) == 1)
  {
      m_shapeB = "*Missing code!*";
      m_shapeBFunctionCode = "*Missing code!*";
      m_shapeBShaderCode = "*Missing code!*\n";
  }
  updateCode();
}

QJsonObject UnionNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_unionData)
  {
    modelJson["shaderCode"] = m_shaderCode;
    modelJson["functionCode"] = m_functionCode;
    modelJson["variableName"] = m_unionData->getVariableName();
    modelJson["shapeA"] = m_shapeA;
    modelJson["shapeAFunctionCode"] = m_shapeAFunctionCode;
    modelJson["shapeAShaderCode"] = m_shapeAShaderCode;
    modelJson["shapeB"] = m_shapeB;
    modelJson["shapeBFunctionCode"] = m_shapeBFunctionCode;
    modelJson["shapeBShaderCode"] = m_shapeBShaderCode;
  }

  return modelJson;
}

void UnionNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue fc = _p["functionCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue sa = _p["shapeA"];
  QJsonValue safc = _p["shapeAFunctionCode"];
  QJsonValue sasc = _p["shapeAShaderCode"];
  QJsonValue sb = _p["shapeB"];
  QJsonValue sbfc = _p["shapeBFunctionCode"];
  QJsonValue sbsc = _p["shapeBShaderCode"];

  m_unionData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_unionData->setShaderCode(shaderCode);
  }

  if (!fc.isUndefined())
  {
    QString functionCode = fc.toString();
    m_unionData->setFunctionCode(functionCode);
  }

  if (!vn.isUndefined())
  {
    QString variableName = vn.toString();
    m_unionData->setVariableName(variableName);
  }

  if (!sa.isUndefined())
  {
    QString shapeA = sa.toString();
    m_unionData->setShapeA(shapeA);
  }

  if (!safc.isUndefined())
  {
    QString shapeAFunctionCode = safc.toString();
    m_shapeAFunctionCode = shapeAFunctionCode;
  }

  if (!sasc.isUndefined())
  {
    QString shapeAShaderCode = sasc.toString();
    m_shapeAShaderCode = shapeAShaderCode;
  }

  if (!sb.isUndefined())
  {
    QString shapeB = sb.toString();
    m_unionData->setShapeB(shapeB);
  }

  if (!sbfc.isUndefined())
  {
    QString shapeBFunctionCode = sbfc.toString();
    m_shapeBFunctionCode = shapeBFunctionCode;
  }

  if (!sbsc.isUndefined())
  {
    QString shapeBShaderCode = sbsc.toString();
    m_shapeBShaderCode = shapeBShaderCode;
  }
}

void UnionNode::updateCode()
{
    // Setup variables
    m_shaderCode =
    m_shapeAShaderCode +
    m_shapeBShaderCode +
    "distance = min(" + m_shapeA + ", " + m_shapeB + ");\n";

    m_functionCode = m_shapeAFunctionCode + m_shapeBFunctionCode;

    // Update node data
    m_unionData->setVariableName("0");
    m_unionData->setShapeA(m_shapeA);
    m_unionData->setShapeB(m_shapeB);
    m_unionData->setShaderCode(m_shaderCode);
    m_unionData->setFunctionCode(m_functionCode);
    m_codeEditor->setPlainText(m_shaderCode);

    // Tell connected node to update received data
    Q_EMIT dataUpdated(0);
}

void UnionNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}