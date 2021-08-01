#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include <nodes/Node>
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
using QtNodes::Node;

class NodeEditorWidget : public QGroupBox
{
    Q_OBJECT
public:
    NodeEditorWidget(NGLScene *_scene);
    QtNodes::FlowScene* getNodeEditorScene() { return m_nodeEditorScene; }
    void setupNodeGraph();

public slots:
    void compileButtonClicked();
    void pauseButtonClicked();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();
    void timerEvent(QTimerEvent *_event);

    std::shared_ptr<DataModelRegistry> registerDataModels();
    void setStyle();

    QtNodes::FlowScene *m_nodeEditorScene;
    QtNodes::FlowView *m_nodeEditorView;

    QPushButton *m_compileButton;
    QPushButton *m_pauseButton;
    QLabel *m_outputLabel;
    QLabel *m_timerLabel;

    bool m_pauseTime = false;
    qint64 m_pausedTime = 0;
    bool m_firstCompile = false;

    NGLScene *m_scene;
};