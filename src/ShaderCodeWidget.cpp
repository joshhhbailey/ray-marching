#include "ShaderCodeWidget.h"

#include <QtWidgets/QFormLayout>
#include <QTime>

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
    m_fontSizeLabel = new QLabel();
    m_fontSizeLabel->setText("Font Size:");
    m_fontSize = new QSpinBox();
    m_fontSize->setValue(11);
    /*m_fontSize->setMinimum(8);
    m_fontSize->setMaximum(72);
    m_fontSize->setMinimumWidth(40);
    m_fontSize->setMaximumWidth(40);*/
    m_compileButton = new QPushButton("Compile");
    m_outputLabel = new QLabel();
    m_outputLabel->setText("[" + QTime::currentTime().toString() + "] Welcome to fragOut!");
}
void ShaderCodeWidget::createLayouts()
{
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(m_codeEditor, 0, 0, 1, 2);
    mainLayout->addWidget(m_fontSizeLabel, 1, 0, 1, 1);
    mainLayout->addWidget(m_fontSize, 1, 1, 1, 1);
    mainLayout->addWidget(m_compileButton, 2, 0, 1, 2);
    mainLayout->addWidget(m_outputLabel, 3, 0, 1, 2);
    setLayout(mainLayout);
}
void ShaderCodeWidget::createConnections()
{
    connect(m_fontSize, SIGNAL(valueChanged(int)), m_codeEditor, SLOT(setFontSize(int)));
    connect(m_compileButton, SIGNAL(clicked()), this, SLOT(compileButtonClicked()));
}

void ShaderCodeWidget::compileButtonClicked()
{
    std::cout << "Retrieving shader code...\n";

    QString shaderCode = m_boilerPlateCode + m_codeEditor->getShaderCode();
    QString string = "] ";

    if (m_scene->compileShaderCode(shaderCode))
    {
        string += "Shader compilation successful!";
    }
    else
    {
        std::vector<GLchar> error = m_scene->getShaderErrorMessage();
        for (int i = 0; i < error.size(); ++i)
        {
            string += error[i];
        }
    }
    m_outputLabel->setText("[" + QTime::currentTime().toString() + string);
}