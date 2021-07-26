#include <QtWidgets/QWidget>

#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/DataModelRegistry>
#include <nodes/ConnectionStyle>

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;

class NodeEditorContainer : public QWidget
{
    Q_OBJECT
public:
    NodeEditorContainer();

public slots:
    void openFile();
    void saveFile();
    void saveAsFile();

private:
    void createWidgets();
    void createLayouts();

    std::shared_ptr<DataModelRegistry> registerDataModels();
    void setStyle();

    QtNodes::FlowScene *m_nodeEditorScene;
    QtNodes::FlowView *m_nodeEditorView;
};