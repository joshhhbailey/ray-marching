#pragma once

#include <QtWidgets/QGroupBox>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include "NGLScene.h"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;

class NodeEditorWidget : public QGroupBox
{
    Q_OBJECT
public:
    NodeEditorWidget(NGLScene *_scene);
    QtNodes::FlowScene* getNodeEditorScene() { return m_nodeEditorScene; }

private:
    void createWidgets();
    void createLayouts();
    void setupNodeGraph();

    std::shared_ptr<DataModelRegistry> registerDataModels();
    void setStyle();

    QtNodes::FlowScene *m_nodeEditorScene;
    QtNodes::FlowView *m_nodeEditorView;

    NGLScene *m_scene;
};