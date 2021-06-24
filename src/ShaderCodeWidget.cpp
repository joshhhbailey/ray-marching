#include "ShaderCodeWidget.h"

#include <QtWidgets/QFormLayout>

ShaderCodeWidget::ShaderCodeWidget()
{
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
    connect(this->m_compileButton, SIGNAL(clicked()), this, SLOT(compileShaderCode()));
}

void ShaderCodeWidget::compileShaderCode()
{
    // 
}