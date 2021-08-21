///  @file BooleanNode.cpp
///  @brief Handles logic for Boolean Operator node

#include <ngl/Vec3.h>

#include "BooleanNode.h"

BooleanNode::BooleanNode()
{
    m_booleanData = std::make_shared<ShaderCodeData>();
    m_booleanData->setIsBooleanOp(true);
    m_booleanWidget = new BooleanNodeWidget;
    m_codeEditor = new CodeEditor();
    m_codeEditor->setWindowTitle("Boolean Node");
    updateCode();
    m_codeEditor->setReadOnly(true);
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void BooleanNode::createConnections()
{
  connect(m_booleanWidget->getIDWidget(), SIGNAL(valueChanged(int)), this, SLOT(updateCode()));
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
                return QStringLiteral("SDF Input A");
            }
            else if (_portIndex == 1)
            {
                return QStringLiteral("SDF Input B");
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
            if (m_receivedNodeA->getIsBooleanOp())
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

            m_materialMapA.clear();
            m_materialMapA = m_receivedNodeA->getMaterialMap();
        }
    }

    if (_portIndex == 1)
    {
        m_receivedNodeB = std::dynamic_pointer_cast<ShaderCodeData>(_data);
        if (m_receivedNodeB)
        {
            // Input: Boolean Operator
            if (m_receivedNodeB->getIsBooleanOp())
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

            m_materialMapB.clear();
            m_materialMapB = m_receivedNodeB->getMaterialMap();
        }
    }
    if (m_receivedNodeA && m_receivedNodeB)
    {
      // Invalid combinations of inputs
      if ((!m_receivedNodeA->getIsSDF() && !m_receivedNodeA->getIsBooleanOp() && !m_receivedNodeB->getIsSDF() && m_receivedNodeB->getIsBooleanOp()) ||             // Both NOT SDFs
          ((m_receivedNodeA->getIsSDF() || m_receivedNodeA->getIsBooleanOp()) &&
                                           !m_receivedNodeB->getIsSDF() &&
                                           !m_receivedNodeB->getIsBooleanOp()) ||       // 1 SDF/Bool + Other
          ((m_receivedNodeB->getIsSDF() || m_receivedNodeB->getIsBooleanOp()) &&
                                          !m_receivedNodeA->getIsSDF() &&
                                          !m_receivedNodeA->getIsBooleanOp())           // 1 SDF/Bool + Other
         )
      {
        m_modelValidationState = NodeValidationState::Error;
        m_modelValidationError = QStringLiteral("Invalid input(s)!");
      }
      else
      {
        // Both inputs are Boolean Operators
        if (m_receivedNodeA->getIsBooleanOp() && m_receivedNodeB->getIsBooleanOp())
        {
          m_booleanWidget->getIDWidget()->setEnabled(true);
          m_booleanWidget->getIDWidget()->show();
          m_shapeAShaderCode = m_receivedNodeA->getShaderCode();
          m_shapeBShaderCode = m_receivedNodeB->getShaderCode();
        }
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
      m_materialMapA.clear();
  }
  if (_connection.getPortIndex(PortType::In) == 1)
  {
      m_shapeB = "/*Missing code!*/";
      m_shapeBShaderCode = "/*Missing code!*/\n";
      m_shapeBfunctionCall = "/*Missing code!*/";
      m_shapeBisBoolean = false;
      m_receivedNodeB = nullptr;
      m_materialMapB.clear();
  }
  m_materialMapCombined.clear();
  m_booleanWidget->getIDWidget()->setEnabled(false);
  m_booleanWidget->getIDWidget()->hide();
  updateCode();
  m_modelValidationState = NodeValidationState::Error;
  m_modelValidationError = QStringLiteral("Missing input(s)!");
}

QJsonObject BooleanNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_booleanData)
  {
    modelJson["operator"] = m_booleanWidget->getOperatorCB()->currentIndex();
    modelJson["operatorCall"] = m_operatorCall;
    modelJson["id"] = m_booleanWidget->getIDWidget()->value();
  }

  return modelJson;
}

void BooleanNode::restore(QJsonObject const &_p)
{
  QJsonValue o = _p["operator"];
  QJsonValue oc = _p["operatorCall"];
  QJsonValue id = _p["id"];

  m_booleanData = std::make_shared<ShaderCodeData>();

  if (!o.isUndefined())
  {
    int op = o.toInt();
    m_booleanWidget->getOperatorCB()->setCurrentIndex(op);
  }

  if (!oc.isUndefined())
  {
    QString operatorCall = oc.toString();
    m_operatorCall = operatorCall;
  }

  if (!id.isUndefined())
  {
    m_booleanWidget->getIDWidget()->setValue(id.toInt());
  }
  
  m_booleanData->setIsBooleanOp(true);
}

void BooleanNode::updateCode()
{
    // Combine material maps
    for (auto A : m_materialMapA.keys())
    {
      m_materialMapCombined.insert(A, m_materialMapA.value(A));
    }
    for (auto B : m_materialMapB.keys())
    {
      m_materialMapCombined.insert(B, m_materialMapB.value(B));
    }

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

    // Code setup
    if (m_shapeAisBoolean && m_shapeBisBoolean)
    {
      int id = m_booleanWidget->getIDWidget()->value();
      QString varA = "boolOpA_" + QString::number(id);
      QString varB = "boolOpB_" + QString::number(id);

      m_shaderCode =
      m_shapeAShaderCode +
      "float " + varA + " = distance;\n" +
      m_shapeBShaderCode +
      "float " + varB + " = distance;\n" +
      "distance = " + m_operatorCall + "(" + varA + ", " + varB + ");\n";
    }
    else if (m_shapeAisBoolean)
    {
      m_shapeA = "distance";

      m_shaderCode =
      m_shapeAShaderCode +
      "float " + m_shapeB + m_shapeBfunctionCall +
      "distance = " + m_operatorCall + "(" + m_shapeA + ", " + m_shapeB + ");\n";
    }
    else if (m_shapeBisBoolean)
    {
      m_shapeB = "distance";

      m_shaderCode =
      m_shapeBShaderCode +
      "float " + m_shapeA + m_shapeAfunctionCall +
      "distance = " + m_operatorCall + "(" + m_shapeA + ", " + m_shapeB + ");\n";
    }
    else
    {
      m_shaderCode =
      "float " + m_shapeA + m_shapeAfunctionCall +
      "float " + m_shapeB + m_shapeBfunctionCall +
      "distance = " + m_operatorCall + "(" + m_shapeA + ", " + m_shapeB + ");\n";
    }

    // Update node data
    m_booleanData->setVariableName("0");
    m_booleanData->setShaderCode(m_shaderCode);
    m_booleanData->setMaterialMap(m_materialMapCombined);
    m_codeEditor->setPlainText(m_shaderCode);

    // Tell connected node to update received data
    Q_EMIT dataUpdated(0);
}

void BooleanNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}