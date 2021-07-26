#pragma once

#include "RayMarchNode.h"
#include <iostream>

RayMarchNode::RayMarchNode()
{
    createWidgets();
    createConnections();
}

QString RayMarchNode::caption() const
{
    return QString("Ray March");
}

QString RayMarchNode::name() const
{
    return QString("Ray March");
}

void RayMarchNode::createWidgets()
{
    m_compileButton = new QPushButton("Compile");
}

void RayMarchNode::createConnections()
{
    connect(m_compileButton, SIGNAL(clicked()), this, SLOT(compileButtonClicked()));
}

void RayMarchNode::compileButtonClicked()
{
    std::cout << "node\n";
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
    return m_compileButton;
}

/*QJsonObject RayMarchNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (_number)
    modelJson["number"] = QString::number(_number->number());

  return modelJson;
}

void RayMarchNode::restore(QJsonObject const &_p)
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
