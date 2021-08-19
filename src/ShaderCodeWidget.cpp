///  @file ShaderCodeWidget.cpp
///  @brief Main Shader Code Editor widget

#include <QtWidgets/QFormLayout>
#include <QTime>
#include <QTextStream>

#include <iostream>

#include "ShaderCodeWidget.h"

ShaderCodeWidget::ShaderCodeWidget(NGLScene *_scene)
{
    m_scene = _scene;
    setTitle("Shader Code");
    createWidgets();
    createLayouts();
    createConnections();
    startTimer(10);
}

void ShaderCodeWidget::createWidgets()
{
    m_codeEditor = new CodeEditor();
    m_syntaxHighlighter = new SyntaxHighlighter(m_codeEditor->document());

    m_libraryEditor = new CodeEditor();
    m_libraryEditor->setReadOnly(true);
    m_libraryHighlighter = new SyntaxHighlighter(m_libraryEditor->document());

    m_fontSizeLabel = new QLabel();
    m_fontSizeLabel->setText("Font Size:");

    m_fontSize = new QSpinBox();
    m_fontSize->setValue(11);
    m_fontSize->setMinimum(8);
    m_fontSize->setMaximum(48);

    m_compileButton = new QPushButton("Compile");
    m_pauseButton = new QPushButton("Pause/Unpause");
    m_libraryButton = new QPushButton("View hg_sdf");

    m_outputLabel = new QLabel();
    m_outputLabel->setText("[" + QTime::currentTime().toString() + "] Welcome to fragOut!");

    m_timerLabel = new QLabel();
    
}

void ShaderCodeWidget::createLayouts()
{
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(m_codeEditor, 0, 0, 1, 3);
    mainLayout->addWidget(m_fontSizeLabel, 1, 0, 1, 1);
    mainLayout->addWidget(m_fontSize, 1, 1, 1, 2);
    mainLayout->addWidget(m_compileButton, 2, 0, 1, 1);
    mainLayout->addWidget(m_pauseButton, 2, 1, 1, 1);
    mainLayout->addWidget(m_libraryButton, 2, 2, 1, 1);
    mainLayout->addWidget(m_outputLabel, 3, 0, 1, 3);
    mainLayout->addWidget(m_timerLabel, 4, 0, 1, 3);
    setLayout(mainLayout);
}

void ShaderCodeWidget::createConnections()
{
    connect(m_fontSize, SIGNAL(valueChanged(int)), m_codeEditor, SLOT(setFontSize(int)));
    connect(m_compileButton, SIGNAL(clicked()), this, SLOT(compileButtonClicked()));
    connect(m_pauseButton, SIGNAL(clicked()), this, SLOT(pauseButtonClicked()));
    connect(m_libraryButton, SIGNAL(clicked()), this, SLOT(libraryButtonClicked()));
}

void ShaderCodeWidget::compileButtonClicked()
{
    std::cout << "Retrieving shader code...\n";

    QString string = "] ";

    if (m_scene->compileShaderCode(m_codeEditor->getShaderCode(), true))
    {
        string += "Shader compilation successful!";
        m_pausedTime = 0;
        m_pauseTime = false;
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

void ShaderCodeWidget::pauseButtonClicked()
{
    if (m_scene->getShaderEditor())
    {
        if (!m_pauseTime)
        {
            m_pausedTime += m_scene->pauseTime();
            m_pauseTime = true;
        }
        else
        {
            m_scene->unpauseTime(m_pausedTime);
            m_pauseTime = false;
        }
    }
}

void ShaderCodeWidget::libraryButtonClicked()
{
    if (!m_libraryLoaded)
    {
        loadLibrary();
    }
    if (m_libraryLoaded)
    {
        m_libraryEditor->show();
        m_libraryEditor->raise();
    }
}

void ShaderCodeWidget::loadLibrary()
{
    QString filename = "shaders/hg_sdf.glsl";
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString text = in.readAll();
        m_libraryEditor->setPlainText(text);
        file.close();
        m_libraryLoaded = true;
    }
    else
    {
        std::cout << "Unable to open " << filename.toStdString() << "\n";
    }
}

void ShaderCodeWidget::timerEvent(QTimerEvent *_event)
{
    // Update compilation timer
    if (m_scene->getShaderEditor())
    {
        if (!m_pauseTime)
        {
            QString compTime = QString::number(m_scene->getCompilationTime() + (m_pausedTime / 1000.0f));
            m_timerLabel->setText(compTime);
        }
    }
    else
    {
        m_timerLabel->setText("0.000");
    }
    update();
}