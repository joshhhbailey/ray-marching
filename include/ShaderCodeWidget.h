#pragma once
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include "NGLScene.h"
#include "CodeEditor.h"
#include "SyntaxHighlighter.h"

class ShaderCodeWidget : public QGroupBox
{
    Q_OBJECT
public:
    ShaderCodeWidget(NGLScene *_scene);
    CodeEditor* getCodeEditor() { return m_codeEditor; }
    
    QString getBoilerPlateCode() { return m_boilerPlateCode; }

public slots:
    void compileButtonClicked();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();

    CodeEditor *m_codeEditor;
    SyntaxHighlighter *m_syntaxHighlighter;
    QLabel *m_fontSizeLabel;
    QSpinBox *m_fontSize;
    QPushButton *m_compileButton;
    QLabel *m_outputLabel;

    NGLScene *m_scene;

    QString m_boilerPlateCode =
    "#version 400 core"
    "\n"
    "layout (location = 0) out vec4 fragColour;\n"
    "\n"
    "uniform vec3 cam_pos;\n"
    "uniform float time;\n"
    "uniform vec2 resolution;\n"
    "uniform vec2 mouse;\n"
    "in vec2 uv;\n"
    "\n";
};