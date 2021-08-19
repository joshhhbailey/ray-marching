///  @file MaterialNode.cpp
///  @brief Handles logic for Material node

#include <ngl/Vec3.h>

#include "MaterialNode.h"

MaterialNode::MaterialNode()
{
    m_material = ngl::Vec3(0.0, 0.0, 0.0);

    m_materialData = std::make_shared<ShaderCodeData>();
    m_materialData->setIsMaterial(true);

    m_materialWidget = new MaterialNodeWidget();

    createConnections();
}

void MaterialNode::createConnections()
{
  connect(m_materialWidget->getColourWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_materialWidget->getColourWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_materialWidget->getColourWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
}

QString MaterialNode::caption() const
{
    return QString("Material");
}

QString MaterialNode::name() const
{
    return QString("Material");
}

unsigned int MaterialNode::nPorts(PortType _portType) const
{
    unsigned int result = 1;

    switch (_portType)
    {
        case PortType::In:
        {
            result = 0;
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

bool MaterialNode::portCaptionVisible(PortType _portType, PortIndex _portIndex) const
{
    Q_UNUSED(_portType);
    Q_UNUSED(_portIndex);
    return true;
}

QString MaterialNode::portCaption(PortType _portType, PortIndex _portIndex) const
{
    switch (_portType)
    {
        case PortType::Out:
        {
            return QStringLiteral("Material Output");
        }

        default:
        {
            break;
        }
    }
    return QString();
}

NodeDataType MaterialNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> MaterialNode::outData(PortIndex)
{
    return m_materialData;
}

QWidget* MaterialNode::embeddedWidget()
{
    return m_materialWidget;
}

QJsonObject MaterialNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_materialData)
  {
    modelJson["R"] = m_materialWidget->getColourWidget()->getVec3().m_x;
    modelJson["G"] = m_materialWidget->getColourWidget()->getVec3().m_y;
    modelJson["B"] = m_materialWidget->getColourWidget()->getVec3().m_z;
  }

  return modelJson;
}

void MaterialNode::restore(QJsonObject const &_p)
{
  QJsonValue R = _p["R"];
  QJsonValue G = _p["G"];
  QJsonValue B = _p["B"];

  m_materialData = std::make_shared<ShaderCodeData>();

  if (!R.isUndefined() && !G.isUndefined() && !B.isUndefined())
  {
    ngl::Vec3 colour = ngl::Vec3(R.toDouble(), G.toDouble(), B.toDouble());
    m_materialWidget->getColourWidget()->setVec3(colour);
  }

  m_materialData->setIsMaterial(true);
}

void MaterialNode::updateNode()
{
  m_material = m_materialWidget->getColourWidget()->getVec3();
  m_materialData->setMaterial(m_material);

  // Tell connected node to update received data
  Q_EMIT dataUpdated(0);
}