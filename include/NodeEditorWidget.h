/// \brief Main Node Editor widget
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef NODEEDITORWIDGET_H_
#define NODEEDITORWIDGET_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QMap>

#include <ConnectionStyle>
#include <DataFlowGraphicsScene>
#include <DataFlowGraphModel>
#include <GraphicsView>
#include <NodeData>
#include <NodeDelegateModelRegistry>

#include "NGLScene.h"
#include "CodeEditor.h"
#include "SyntaxHighlighter.h"

using QtNodes::ConnectionStyle;
using QtNodes::DataFlowGraphicsScene;
using QtNodes::DataFlowGraphModel;
using QtNodes::GraphicsView;
using QtNodes::NodeDelegateModelRegistry;

class NodeEditorWidget : public QGroupBox
{
    Q_OBJECT
public:
    NodeEditorWidget(NGLScene *_scene);
    QtNodes::DataFlowGraphicsScene* getNodeEditorScene() { return m_nodeEditorScene; }
    void setupNodeGraph();

public slots:
    void compileButtonClicked();
    void pauseButtonClicked();
    void inspectCodeButtonClicked();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();
    void timerEvent(QTimerEvent *_event);
    void loadFunctions();

    DataFlowGraphModel* m_dataFlowGraphModel;
    std::shared_ptr<NodeDelegateModelRegistry> registerDataModels();
    void setStyle();

    QtNodes::DataFlowGraphicsScene *m_nodeEditorScene;
    QtNodes::GraphicsView *m_nodeEditorView;

    CodeEditor *m_codeEditor;
    SyntaxHighlighter *m_syntaxHighlighter;

    QPushButton *m_compileButton;
    QPushButton *m_pauseButton;
    QPushButton *m_inspectCodeButton;
    QLabel *m_outputLabel;
    QLabel *m_timerLabel;

    bool m_pauseTime = false;
    qint64 m_pausedTime = 0;
    bool m_firstCompile = false;

    NGLScene *m_scene;

    QMap<QString, QString> m_functions;
};

#endif  // _NODEEDITORWIDGET_H_