/// \brief Main Node Editor widget
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef NODEEDITORWIDGET_H_
#define NODEEDITORWIDGET_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QMap>

#include <nodes/Node>
#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

#include "NGLScene.h"
#include "CodeEditor.h"
#include "SyntaxHighlighter.h"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;
using QtNodes::Node;
using QtNodes::NodeValidationState;

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
    void inspectCodeButtonClicked();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();
    void timerEvent(QTimerEvent *_event);
    void loadFunctions();

    std::shared_ptr<DataModelRegistry> registerDataModels();
    void setStyle();

    QtNodes::FlowScene *m_nodeEditorScene;
    QtNodes::FlowView *m_nodeEditorView;

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