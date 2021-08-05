#include "PlaneNode.h"

#include <ngl/Vec3.h>

#include <iostream>

PlaneNode::PlaneNode()
{
    m_variableName = "plane";
    QString shaderCode = "float " + m_variableName + " = sdPlane(_p, 0);\n";
    QString functionCall = " = sdPlane(_p, 0);\n";

    m_planeData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_planeData->setFunctionCall(functionCall);

    m_planeWidget = new PlaneNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setPlainText(shaderCode);
    m_codeEditor->setReadOnly(true);
    m_codeEditor->hide();
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void PlaneNode::createConnections()
{
  connect(m_planeWidget->getYPosWidget(), SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_planeWidget->getInspectCodeButton(), SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString PlaneNode::caption() const
{
    return QString("Infinite Plane");
}

QString PlaneNode::name() const
{
    return QString("Infinite Plane");
}

unsigned int PlaneNode::nPorts(PortType _portType) const
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

NodeDataType PlaneNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> PlaneNode::outData(PortIndex)
{
    return m_planeData;
}

QWidget* PlaneNode::embeddedWidget()
{
    return m_planeWidget;
}

QJsonObject PlaneNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_planeData)
  {
    modelJson["shaderCode"] = m_planeData->getShaderCode();
    modelJson["variableName"] = m_planeData->getVariableName();
    modelJson["yPos"] = m_planeWidget->getYPosWidget()->value();
  }

  return modelJson;
}

void PlaneNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue yp = _p["yPos"];

  m_planeData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_planeData->setShaderCode(shaderCode);
  }

  if (!vn.isUndefined())
  {
    QString variableName = vn.toString();
    m_planeData->setVariableName(variableName);
  }

  if (!yp.isUndefined())
  {
    double yPos = yp.toDouble();
    m_planeWidget->getYPosWidget()->setValue(yPos);
  }
}

void PlaneNode::updateNode()
{
  // Setup variables
  double yPos = m_planeWidget->getYPosWidget()->value();

  // Convert to string
  QString position = QString::number(yPos);

  // Update function code
  QString shaderCode = "float " + m_variableName + " = sdPlane(_p, " + position + ");\n";
  m_planeData->setShaderCode(shaderCode);

  QString functionCall = " = sdPlane(_p, " + position + ");\n";
  m_planeData->setFunctionCall(functionCall);

  // Tell connected node to update received data
  Q_EMIT dataUpdated(0);
}

void PlaneNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}