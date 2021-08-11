#include "ShaderCodeContainer.h"

#include <QtWidgets/QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>

#include <iostream>

ShaderCodeContainer::ShaderCodeContainer(NGLScene *_scene)
{
    m_scene = _scene;
    createWidgets();
    createLayouts();
}

void ShaderCodeContainer::createWidgets()
{
    m_shaderCodeWidget = new ShaderCodeWidget(m_scene);
}

void ShaderCodeContainer::createLayouts()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_shaderCodeWidget);
    setLayout(mainLayout);
}

void ShaderCodeContainer::newFile()
{
    m_shaderCodeWidget->getCodeEditor()->reset();
    m_filename = QString();
}

void ShaderCodeContainer::openFile()
{
    m_filename = QFileDialog::getOpenFileName(this, "Open File", "", tr("GLSL (*.glsl)"));

    QString shaderCode;
    QFile file(m_filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString text = in.readAll();
        m_shaderCodeWidget->getCodeEditor()->setShaderCode(text);
        file.close();
    }
    else
    {
        std::cout << "Unable to open " << m_filename.toStdString() << "\n";
    }
}

void ShaderCodeContainer::saveFile()
{
    if (m_filename == NULL)
    {
        saveAsFile();
    }
    else
    {
        QString shaderCode = /*m_scene->getBoilerPlateCode() + */m_shaderCodeWidget->getCodeEditor()->getShaderCode();
        QFile file(m_filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << shaderCode;
            file.close();
        }
        else
        {
            std::cout << "Unable to open " << m_filename.toStdString() << "\n";
        }
    }
}

void ShaderCodeContainer::saveAsFile()
{
    m_filename = QFileDialog::getSaveFileName(this, "Save As", "ShaderOutput", tr("GLSL (*.glsl)"));
    if (!m_filename.endsWith("glsl", Qt::CaseInsensitive))
    {
        m_filename += ".glsl";
    }
    saveFile();
}