#include "BooleanNode.h"

#include <ngl/Vec3.h>

#include <iostream>

BooleanNode::BooleanNode()
{
    m_booleanData = std::make_shared<ShaderCodeData>();
    m_booleanData->setBooleanOp(true);
    m_booleanWidget = new BooleanNodeWidget;
    m_codeEditor = new CodeEditor();
    updateCode();
    m_codeEditor->setReadOnly(true);
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void BooleanNode::createConnections()
{
  connect(m_booleanWidget->getOperatorCB(), SIGNAL(currentIndexChanged(int)), this, SLOT(updateCode()));
  connect(m_booleanWidget->getInspectCodeButton(), SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString BooleanNode::caption() const
{
    return QString("Boolean");
}

QString BooleanNode::name() const
{
    return QString("Boolean");
}

unsigned int BooleanNode::nPorts(PortType _portType) const
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

bool BooleanNode::portCaptionVisible(PortType _portType, PortIndex _portIndex) const
{
    Q_UNUSED(_portType);
    Q_UNUSED(_portIndex);
    return true;
}

QString BooleanNode::portCaption(PortType _portType, PortIndex _portIndex) const
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

NodeDataType BooleanNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> BooleanNode::outData(PortIndex)
{
    return m_booleanData;
}

void BooleanNode::setInData(std::shared_ptr<NodeData> _data, PortIndex _portIndex)
{
    // Data received
    if (_portIndex == 0)
    {
        m_receivedNodeA = std::dynamic_pointer_cast<ShaderCodeData>(_data);
        if (m_receivedNodeA)
        {
            // Input: Boolean Operator
            if (m_receivedNodeA->getBooleanOp())
            {
                m_shapeAisBoolean = true;
            }
            // Input: SDF
            else
            {
                m_shapeA = m_receivedNodeA->getVariableName();
            }
            m_shapeAShaderCode = m_receivedNodeA->getShaderCode();
            m_shapeAfunctionCall = m_receivedNodeA->getFunctionCall();
        }
    }

    if (_portIndex == 1)
    {
        m_receivedNodeB = std::dynamic_pointer_cast<ShaderCodeData>(_data);
        if (m_receivedNodeB)
        {
            // Input: Boolean Operator
            if (m_receivedNodeB->getBooleanOp())
            {
                m_shapeBisBoolean = true;
            }
            // Input: SDF
            else
            {
                m_shapeB = m_receivedNodeB->getVariableName();
            }
            m_shapeBShaderCode = m_receivedNodeB->getShaderCode();
            m_shapeBfunctionCall = m_receivedNodeB->getFunctionCall();
        }
    }
    if (m_receivedNodeA && m_receivedNodeB)
    {
      if (m_receivedNodeA->getBooleanOp() && m_receivedNodeB->getBooleanOp())
      {
        m_modelValidationState = NodeValidationState::Error;
        m_modelValidationError = QStringLiteral("Invalid inputs!");
      }
      else
      {
        updateCode();
        m_modelValidationState = NodeValidationState::Valid;
      }
    }
}

QWidget* BooleanNode::embeddedWidget()
{
    return m_booleanWidget;
}

NodeValidationState BooleanNode::validationState() const
{
  return m_modelValidationState;
}

QString BooleanNode::validationMessage() const
{
  return m_modelValidationError;
}

void BooleanNode::inputConnectionDeleted(Connection const&_connection)
{
  if (_connection.getPortIndex(PortType::In) == 0)
  {
      m_shapeA = "/*Missing code!*/";
      m_shapeAShaderCode = "/*Missing code!*/\n";
      m_shapeAfunctionCall = "/*Missing code!*/";
      m_shapeAisBoolean = false;
      m_receivedNodeA = nullptr;
  }
  if (_connection.getPortIndex(PortType::In) == 1)
  {
      m_shapeB = "/*Missing code!*/";
      m_shapeBShaderCode = "/*Missing code!*/\n";
      m_shapeBfunctionCall = "/*Missing code!*/";
      m_shapeBisBoolean = false;
      m_receivedNodeB = nullptr;
  }
  updateCode();
  m_modelValidationState = NodeValidationState::Error;
  m_modelValidationError = QStringLiteral("Missing inputs!");
}

QJsonObject BooleanNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_booleanData)
  {
    modelJson["operatorCall"] = m_operatorCall;
    modelJson["shaderCode"] = m_shaderCode;
    modelJson["shapeA"] = m_shapeA;
    modelJson["shapeABooleanOp"] = m_shapeAisBoolean;
    modelJson["shapeAShaderCode"] = m_shapeAShaderCode;
    modelJson["shapeAfunctionCall"] = m_shapeAfunctionCall;
    modelJson["shapeB"] = m_shapeB;
    modelJson["shapeBBooleanOp"] = m_shapeBisBoolean;
    modelJson["shapeBShaderCode"] = m_shapeBShaderCode;
    modelJson["shapeBfunctionCall"] = m_shapeBfunctionCall;
  }

  return modelJson;
}

void BooleanNode::restore(QJsonObject const &_p)
{
  QJsonValue oc = _p["operatorCall"];
  QJsonValue sc = _p["shaderCode"];
  QJsonValue sa = _p["shapeA"];
  QJsonValue sabo = _p["shapeABooleanOp"];
  QJsonValue sasc = _p["shapeAShaderCode"];
  QJsonValue safc = _p["shapeAfunctionCall"];
  QJsonValue sb = _p["shapeB"];
  QJsonValue sbbo = _p["shapeBBooleanOp"];
  QJsonValue sbsc = _p["shapeBShaderCode"];
  QJsonValue sbfc = _p["shapeBfunctionCall"];

  m_booleanData = std::make_shared<ShaderCodeData>();

  if (!oc.isUndefined())
  {
    QString operatorCall = oc.toString();
    m_operatorCall = operatorCall;
  }

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_booleanData->setShaderCode(shaderCode);
    m_shaderCode = shaderCode;
  }

  if (!sa.isUndefined())
  {
    QString shapeA = sa.toString();
    m_shapeA = shapeA;
  }

  if (!sabo.isUndefined())
  {
    bool shapeAisBoolean = sabo.toBool();
    m_shapeAisBoolean = shapeAisBoolean;
  }

  if (!sasc.isUndefined())
  {
    QString shapeAShaderCode = sasc.toString();
    m_shapeAShaderCode = shapeAShaderCode;
  }

  if (!safc.isUndefined())
  {
    QString shapeAfunctionCall = safc.toString();
    m_shapeAfunctionCall = shapeAfunctionCall;
  }

  if (!sb.isUndefined())
  {
    QString shapeB = sb.toString();
    m_shapeB = shapeB;
  }

  if (!sbbo.isUndefined() )
  {
    bool shapeBisBoolean = sbbo.toBool();
    m_shapeBisBoolean = shapeBisBoolean;
  }

  if (!sbsc.isUndefined())
  {
    QString shapeBShaderCode = sbsc.toString();
    m_shapeBShaderCode = shapeBShaderCode;
  }

  if (!sbfc.isUndefined())
  {
    QString shapeBfunctionCall = sbfc.toString();
    m_shapeBfunctionCall = shapeBfunctionCall;
  }
}

void BooleanNode::updateCode()
{
    // Operator selection
    if (m_booleanWidget->getOperatorCB()->currentIndex() == 0)
    {
      m_operatorCall = "sdIntersection";
    }
    else if (m_booleanWidget->getOperatorCB()->currentIndex() == 1)
    {
      m_operatorCall = "sdUnion";
    }
    else
    {
      m_operatorCall = "sdDifference";
    }

    // Setup variables
    m_shaderCode =
    "float " + m_shapeA + m_shapeAfunctionCall +
    "float " + m_shapeB + m_shapeBfunctionCall +
    "distance = " + m_operatorCall + "(" + m_shapeA + ", " + m_shapeB + ");\n";

    if (m_shapeAisBoolean)
    {
      m_shapeA = "distance";

      m_shaderCode =
      m_shapeAShaderCode +
      "float " + m_shapeB + m_shapeBfunctionCall +
      "distance = " + m_operatorCall + "(" + m_shapeA + ", " + m_shapeB + ");\n";
    }

    if (m_shapeBisBoolean)
    {
      m_shapeB = "distance";

      m_shaderCode =
      m_shapeBShaderCode +
      "float " + m_shapeA + m_shapeAfunctionCall +
      "distance = " + m_operatorCall + "(" + m_shapeA + ", " + m_shapeB + ");\n";
    }

    // Update node data
    m_booleanData->setVariableName("0");
    m_booleanData->setShaderCode(m_shaderCode);
    m_codeEditor->setPlainText(m_shaderCode);

    // Tell connected node to update received data
    Q_EMIT dataUpdated(0);
}

void BooleanNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}