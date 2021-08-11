#include "TorusNode.h"

#include <ngl/Vec2.h>
#include <ngl/Vec3.h>

#include <iostream>

TorusNode::TorusNode()
{
    m_variableName = "torus0";
    QString shaderCode = "float " + m_variableName + " = sdTorus(_p, vec3(0, 0, 0), vec2(0, 0));\n";
    QString functionCall = " = sdTorus(_p, vec3(0, 0, 0), vec2(0, 0));\n";

    m_torusData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_torusData->setFunctionCall(functionCall);

    m_torusWidget = new TorusNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setPlainText(shaderCode);
    m_codeEditor->setReadOnly(true);
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void TorusNode::createConnections()
{
  connect(m_torusWidget->getIDWidget(), SIGNAL(valueChanged(int)), this, SLOT(updateNode()));
  connect(m_torusWidget->getPositionWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->getPositionWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->getPositionWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->getRadiusWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->getRadiusWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_torusWidget->getInspectCodeButton(), SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString TorusNode::caption() const
{
    return QString("Torus");
}

QString TorusNode::name() const
{
    return QString("Torus");
}

unsigned int TorusNode::nPorts(PortType _portType) const
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

NodeDataType TorusNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> TorusNode::outData(PortIndex)
{
    return m_torusData;
}

QWidget* TorusNode::embeddedWidget()
{
    return m_torusWidget;
}

QJsonObject TorusNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_torusData)
  {
    modelJson["shaderCode"] = m_torusData->getShaderCode();
    modelJson["variableName"] = m_torusData->getVariableName();
    modelJson["xPos"] = m_torusWidget->getPositionWidget()->getVec3().m_x;
    modelJson["yPos"] = m_torusWidget->getPositionWidget()->getVec3().m_y;
    modelJson["zPos"] = m_torusWidget->getPositionWidget()->getVec3().m_z;
    modelJson["xRadius"] = m_torusWidget->getRadiusWidget()->getVec2().m_x;
    modelJson["yRadius"] = m_torusWidget->getRadiusWidget()->getVec2().m_y;
    modelJson["id"] = m_torusWidget->getIDWidget()->value();
  }

  return modelJson;
}

void TorusNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue xp = _p["xPos"];
  QJsonValue yp = _p["yPos"];
  QJsonValue zp = _p["zPos"];
  QJsonValue xr  = _p["xRadius"];
  QJsonValue yr  = _p["yRadius"];
  QJsonValue id = _p["id"];

  m_torusData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_torusData->setShaderCode(shaderCode);
  }

  if (!vn.isUndefined())
  {
    QString variableName = vn.toString();
    m_torusData->setVariableName(variableName);
  }

  if (!xp.isUndefined() && !yp.isUndefined() && !zp.isUndefined())
  {
    ngl::Vec3 position = ngl::Vec3(xp.toDouble(), yp.toDouble(), zp.toDouble());
    m_torusWidget->getPositionWidget()->setVec3(position);
  }

  if (!xr.isUndefined() && !yr.isUndefined())
  {
    ngl::Vec2 radius = ngl::Vec2(xr.toDouble(), yr.toDouble());
    m_torusWidget->getRadiusWidget()->setVec2(radius);
  }

  if (!id.isUndefined())
  {
    m_torusWidget->getIDWidget()->setValue(id.toInt());
  }
}

void TorusNode::updateNode()
{
  // Setup variables
  ngl::Vec3 pos = m_torusWidget->getPositionWidget()->getVec3();
  int px = pos.m_x;
  int py = pos.m_y;
  int pz = pos.m_z;

  ngl::Vec2 radiusVec = m_torusWidget->getRadiusWidget()->getVec2();
  int rx = radiusVec.m_x;
  int ry = radiusVec.m_y;

  // Convert to string
  QString position = QString::number(px) + ", " + QString::number(py) + ", " + QString::number(pz);
  QString radius = QString::number(rx) + ", " + QString::number(ry);

  // Update node data
  m_variableName = "torus" + QString::number(m_torusWidget->getIDWidget()->value());
  m_torusData->setVariableName(m_variableName);

  QString shaderCode = "float " + m_variableName + " = sdTorus(_p, vec3(" + position + "), vec2(" + radius + "));\n";
  m_torusData->setShaderCode(shaderCode);

  QString functionCall = " = sdTorus(_p, vec3(" + position + "), vec2(" + radius + "));\n";
  m_torusData->setFunctionCall(functionCall);

  // Tell connected node to update received data
  Q_EMIT dataUpdated(0);
}

void TorusNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}