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

std::shared_ptr<NodeData> SphereNode::outData(PortIndex)
{
    return std::make_shared<SphereData>();
}

QWidget* SphereNode::embeddedWidget()
{
    return nullptr;
}

/*QJsonObject SphereNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number)
    modelJson["number"] = QString::number(_number->number());

  return modelJson;
}

void SphereNode::restore(QJsonObject const &_p)
{
  QJsonValue v = _p["number"];

  if (!v.isUndefined())
  {
    QString strNum = v.toString();

    bool   ok;
    double d = strNum.toDouble(&ok);
    if (ok)
    {
      _number = std::make_shared<DecimalData>(d);
      _lineEdit->setText(strNum);
    }
  }
}*/
