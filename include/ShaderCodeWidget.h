#pragma once
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>

#include "NGLScene.h"
#include "CodeEditorWidget.h"
#include "SyntaxHighlighter.h"

class ShaderCodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    ShaderCodeWidget();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();

    void compileShaderCode();

    CodeEditorWidget *m_codeEditorWidget;
    SyntaxHighlighter *m_syntaxHighlighter;
    QPushButton *m_compileButton;
};