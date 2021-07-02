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
    m_codeEditor = new CodeEditor();
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());
    m_compileButton = new QPushButton("Compile");
}
void ShaderCodeWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addWidget(m_codeEditor);
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

    QString shaderCode = m_boilerPlateCode + m_codeEditor->getShaderCode();
    m_scene->compileShaderCode(shaderCode);
}