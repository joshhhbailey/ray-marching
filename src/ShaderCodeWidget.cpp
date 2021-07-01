#include "ShaderCodeWidget.h"

#include <QtWidgets/QFormLayout>

#include <iostream>

ShaderCodeWidget::ShaderCodeWidget(NGLScene *_scene)
{
    m_scene = _scene;
    setTitle("Shader Code");
    createWidgets();
    createLayouts();
    createConnections();
}

void ShaderCodeWidget::createWidgets()
{
    m_codeEditorWidget = new CodeEditorWidget();
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditorWidget->document());
    m_compileButton = new QPushButton("Compile");
}
void ShaderCodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addWidget(m_codeEditorWidget);
    mainLayout->addRow(m_compileButton);
    setLayout(mainLayout);
}
void ShaderCodeWidget::createConnections()
{
    connect(this->m_compileButton, SIGNAL(clicked()), this, SLOT(compileButtonClicked()));
}

void ShaderCodeWidget::compileButtonClicked()
{
    std::cout << "Retrieving shader code...\n";
    
    // Boiler plate code (not visible to user)
    const char code[] =
    "#version 410 core"
    "\n"
    "layout (location = 0) out vec4 fragColour;\n"
    "\n"
    "uniform vec3 cam_pos;\n"
    "uniform float time;\n"
    "uniform vec2 resolution;\n"
    "uniform vec2 mouse;\n"
    "in vec2 uv;\n"
    "\n";

    QString shaderCode = code + m_codeEditorWidget->retrieveShaderCode();
    m_scene->compileShaderCode(shaderCode);
}