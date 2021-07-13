#pragma once

#include "TestNode.h"

QString TestNode::caption() const
{
    return QString("Test Node");
}

QString TestNode::name() const
{
    return QString("TestNode");
}

unsigned int TestNode::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType)
    {
        case PortType::In:
        {
            result = 2;
            break;
        }
        case PortType::Out:
        {
            result = 2;
            break;
        }
        case PortType::None:
        {
            break;
        }
    }
    return result;
}

NodeDataType TestNode::dataType(PortType portType, PortIndex portIndex) const
{
    switch (portType)
    {
        case PortType::In:
            switch (portIndex)
            {
                case 0:
                {
                    return MyNodeData().type();
                }
                case 1:
                {
                    return SimpleNodeData().type();
                }
            }
            break;

        case PortType::Out:
            switch (portIndex)
            {
                case 0:
                {
                    return MyNodeData().type();
                }
                case 1:
                {
                    return SimpleNodeData().type();
                }
            }
            break;

        case PortType::None:
            break;
    }
    // FIXME: control may reach end of non-void function [-Wreturn-type]
    return NodeDataType();
  }

std::shared_ptr<NodeData> TestNode::outData(PortIndex port)
{
    if (port < 1)
    {
        return std::make_shared<MyNodeData>();
    }
    return std::make_shared<SimpleNodeData>();
}

void TestNode::setInData(std::shared_ptr<NodeData>, int)
{
    //
}

QWidget* TestNode::embeddedWidget()
{
    return nullptr;
}
