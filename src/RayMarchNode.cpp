#pragma once

#include "RayMarchNode.h"

#include "ShaderCodeWidget.h"

RayMarchNode::RayMarchNode()
{

}

QString RayMarchNode::caption() const
{
    return QString("Ray March");
}

QString RayMarchNode::name() const
{
    return QString("Ray March");
}

unsigned int RayMarchNode::nPorts(PortType _portType) const
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
            result = 0;
            break;
        }
        case PortType::None:
        {
            break;
        }
    }
    return result;
}

NodeDataType RayMarchNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return RayMarchData().type();
}

std::shared_ptr<NodeData> RayMarchNode::outData(PortIndex)
{
  std::shared_ptr<NodeData> ptr;
  return ptr;
}


void RayMarchNode::setInData(std::shared_ptr<NodeData>, int)
{
  //
}

QWidget* RayMarchNode::embeddedWidget()
{
  return nullptr;
}

QJsonObject RayMarchNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  return modelJson;
}

void RayMarchNode::restore(QJsonObject const &_p)
{

}
