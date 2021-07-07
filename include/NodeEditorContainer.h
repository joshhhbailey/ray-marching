#include <QtWidgets/QWidget>

class NodeEditorContainer : public QWidget
{
    Q_OBJECT
public:
    NodeEditorContainer();

private:
    void createWidgets();
    void createLayouts();
};