#pragma once

#include "SphereNode.h"

QString SphereNode::caption() const
{
    return QString("Sphere");
}

QString SphereNode::name() const
{
    return QString("Sphere");
}

unsigned int SphereNode::nPorts(PortType _portType) const
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

NodeDataType SphereNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return SphereData().type();
}

void SphereNode::setInData(std::shared_ptr<NodeData>, int)
{

}

std::shared_ptr<NodeData> SphereNode::outData(PortIndex)
{
    return std::make_shared<SphereData>();
}

QWidget* SphereNode::embeddedWidget()
{
    return nullptr;
}

QJsonObject SphereNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  return modelJson;
}

void SphereNode::restore(QJsonObject const &_p)
{
  
}
