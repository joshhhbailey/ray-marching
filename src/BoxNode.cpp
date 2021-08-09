#include "BoxNode.h"

#include <ngl/Vec3.h>

#include <iostream>

BoxNode::BoxNode()
{
    m_variableName = "box0";
    QString shaderCode = "float " + m_variableName + " = sdBox(_p, vec3(0, 0, 0), vec3(0, 0, 0));\n";
    QString functionCall = " = sdBox(_p, vec3(0, 0, 0), vec3(0, 0, 0));\n";

    m_boxData = std::make_shared<ShaderCodeData>(shaderCode, m_variableName);
    m_boxData->setFunctionCall(functionCall);

    m_boxWidget = new BoxNodeWidget();
    m_codeEditor = new CodeEditor();
    m_codeEditor->setPlainText(shaderCode);
    m_codeEditor->setReadOnly(true);
    m_codeEditor->hide();
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    createConnections();
}

void BoxNode::createConnections()
{
  connect(m_boxWidget->getIDWidget(), SIGNAL(valueChanged(int)), this, SLOT(updateNode()));
  connect(m_boxWidget->getPositionWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->getPositionWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->getPositionWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->getSizeWidget()->m_xField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->getSizeWidget()->m_yField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->getSizeWidget()->m_zField, SIGNAL(valueChanged(double)), this, SLOT(updateNode()));
  connect(m_boxWidget->getInspectCodeButton(), SIGNAL(clicked()), this, SLOT(inspectCodeButtonClicked()));
}

QString BoxNode::caption() const
{
    return QString("Box");
}

QString BoxNode::name() const
{
    return QString("Box");
}

unsigned int BoxNode::nPorts(PortType _portType) const
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

NodeDataType BoxNode::dataType(PortType _portType, PortIndex _portIndex) const
{
    return ShaderCodeData().type();
}

std::shared_ptr<NodeData> BoxNode::outData(PortIndex)
{
    return m_boxData;
}

QWidget* BoxNode::embeddedWidget()
{
    return m_boxWidget;
}

QJsonObject BoxNode::save() const
{
  QJsonObject modelJson = NodeDataModel::save();

  if (m_boxData)
  {
    modelJson["shaderCode"] = m_boxData->getShaderCode();
    modelJson["variableName"] = m_boxData->getVariableName();
    modelJson["xPos"] = m_boxWidget->getPositionWidget()->getVec3().m_x;
    modelJson["yPos"] = m_boxWidget->getPositionWidget()->getVec3().m_y;
    modelJson["zPos"] = m_boxWidget->getPositionWidget()->getVec3().m_z;
    modelJson["xSize"] = m_boxWidget->getSizeWidget()->getVec3().m_x;
    modelJson["ySize"] = m_boxWidget->getSizeWidget()->getVec3().m_y;
    modelJson["zSize"] = m_boxWidget->getSizeWidget()->getVec3().m_z;
    modelJson["id"] = m_boxWidget->getIDWidget()->value();
  }

  return modelJson;
}

void BoxNode::restore(QJsonObject const &_p)
{
  QJsonValue sc = _p["shaderCode"];
  QJsonValue vn = _p["variableName"];
  QJsonValue xp = _p["xPos"];
  QJsonValue yp = _p["yPos"];
  QJsonValue zp = _p["zPos"];
  QJsonValue xs  = _p["xSize"];
  QJsonValue ys  = _p["ySize"];
  QJsonValue zs  = _p["zSize"];
  QJsonValue id = _p["id"];

  m_boxData = std::make_shared<ShaderCodeData>();

  if (!sc.isUndefined())
  {
    QString shaderCode = sc.toString();
    m_boxData->setShaderCode(shaderCode);
  }

  if (!vn.isUndefined())
  {
    QString variableName = vn.toString();
    m_boxData->setVariableName(variableName);
  }

  if (!xp.isUndefined() && !yp.isUndefined() && !zp.isUndefined())
  {
    ngl::Vec3 position = ngl::Vec3(xp.toDouble(), yp.toDouble(), zp.toDouble());
    m_boxWidget->getPositionWidget()->setVec3(position);
  }

  if (!xs.isUndefined() && !ys.isUndefined() && !zs.isUndefined())
  {
    ngl::Vec3 size = ngl::Vec3(xs.toDouble(), ys.toDouble(), zs.toDouble());
    m_boxWidget->getSizeWidget()->setVec3(size);
  }

  if (!id.isUndefined())
  {
    m_boxWidget->getIDWidget()->setValue(id.toInt());
  }
}

void BoxNode::updateNode()
{
  // Setup variables
  ngl::Vec3 pos = m_boxWidget->getPositionWidget()->getVec3();
  int px = pos.m_x;
  int py = pos.m_y;
  int pz = pos.m_z;

  ngl::Vec3 sizeVec = m_boxWidget->getSizeWidget()->getVec3();
  int sx = sizeVec.m_x;
  int sy = sizeVec.m_y;
  int sz = sizeVec.m_z;

  // Convert to string
  QString position = QString::number(px) + ", " + QString::number(py) + ", " + QString::number(pz);
  QString size = QString::number(sx) + ", " + QString::number(sy) + ", " + QString::number(sz);

  // Update node data
  m_variableName = "box" + QString::number(m_boxWidget->getIDWidget()->value());
  m_boxData->setVariableName(m_variableName);

  QString shaderCode = "float " + m_variableName + " = sdBox(_p, vec3(" + position + "), vec3(" + size + "));\n";
  m_boxData->setShaderCode(shaderCode);

  QString functionCall = " = sdBox(_p, vec3(" + position + "), vec3(" + size + "));\n";
  m_boxData->setFunctionCall(functionCall);

  // Tell connected node to update received data
  Q_EMIT dataUpdated(0);
}

void BoxNode::inspectCodeButtonClicked()
{
  m_codeEditor->show();
  m_codeEditor->raise();
}