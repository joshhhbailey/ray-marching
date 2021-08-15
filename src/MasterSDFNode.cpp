#include "MasterSDFNode.h"

unsigned int MasterSDFNode::nPorts(PortType _portType) const
{
    unsigned int result = 1;

    switch (_portType)
    {
        case PortType::In:
        {
            result = 1;
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

NodeDataType MasterSDFNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

bool MasterSDFNode::portCaptionVisible(PortType _portType, PortIndex _portIndex) const
{
    Q_UNUSED(_portType);
    Q_UNUSED(_portIndex);
    return true;
}

QString MasterSDFNode::portCaption(PortType _portType, PortIndex _portIndex) const
{
    switch (_portType)
    {
        case PortType::In:
        {
            if (_portIndex == 0)
            {
                return QStringLiteral("Material Input");
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

NodeValidationState MasterSDFNode::validationState() const
{
  return m_modelValidationState;
}

QString MasterSDFNode::validationMessage() const
{
  return m_modelValidationError;
}

void MasterSDFNode::inputConnectionDeleted(Connection const&)
{
  m_modelValidationState = NodeValidationState::Warning;
  m_modelValidationError = QStringLiteral("Missing material!");
  m_receivedNode = nullptr;
  m_materialMap.clear();
  m_materialMap.insert(m_variableName, ngl::Vec3(1.0f, 1.0f, 1.0f));
  m_nodeData->setMaterialMap(m_materialMap);
  updateNode();
}

void MasterSDFNode::setInData(std::shared_ptr<NodeData> _data, PortIndex _portIndex)
{
    m_receivedNode = std::dynamic_pointer_cast<ShaderCodeData>(_data);

    // Data received
    if (m_receivedNode)
    {
      if (m_receivedNode->getIsMaterial())
      {
        if (_portIndex == 0)
        {
            m_materialMap.clear();
            m_materialMap.insert(m_variableName, m_receivedNode->getMaterial());
            m_nodeData->setMaterialMap(m_materialMap);

            m_modelValidationState = NodeValidationState::Valid;
        }
      }
      else
      {
        m_modelValidationState = NodeValidationState::Error;
        m_modelValidationError = QStringLiteral("Invalid input!");
      }
    }
    updateNode();
}