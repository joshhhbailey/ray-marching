#include "AboutWidget.h"

#include <QtWidgets/QFormLayout>

AboutWidget::AboutWidget()
{
    setTitle("About");
    setAlignment(Qt::AlignHCenter);
    createWidgets();
    createLayouts();
}

void AboutWidget::createWidgets()
{
    m_welcomeLabel = new QLabel();
    m_welcomeLabel->setText("<b>Welcome to fragOut!</b>");
    m_welcomeLabel->setAlignment(Qt::AlignCenter);

    m_descriptionLabel = new QLabel();
    m_descriptionLabel->setText("This tool has been developed with the intention of providing\n"
                                "both artists and programmers with the ability to create 3D\n"
                                "shaders, using Signed Distance Functions (SDFs) and Ray\n"
                                "Marching algorithms, utilising the fragment shader pipeline.\n");
    m_descriptionLabel->setAlignment(Qt::AlignCenter);
    
    m_CETitleLabel = new QLabel();
    m_CETitleLabel->setText("<b>Code Editor:</b>");
    m_CETitleLabel->setAlignment(Qt::AlignCenter);

    m_CEDescriptionLabel = new QLabel();
    m_CEDescriptionLabel->setText("Provides users with limitless possibilities with direct access\n"
                                  "to the shader code, uniforms and the 'hg_sdf' library.\n");
    m_CEDescriptionLabel->setAlignment(Qt::AlignCenter);

    m_NETitleLabel = new QLabel();
    m_NETitleLabel->setText("<b>Node Editor:</b>");
    m_NETitleLabel->setAlignment(Qt::AlignCenter);

    m_NEDescriptionLabel = new QLabel();
    m_NEDescriptionLabel->setText("Provides users with little to no programming experience with\n"
                                  "a higher level node-based toolset, to create shaders. It also\n"
                                  "serves the purpose of a teaching / learning tool, featuring\n"
                                  "the ability view the shader code from 'under the hood'.\n");
    m_NEDescriptionLabel->setAlignment(Qt::AlignCenter);

    m_inspiredLabel = new QLabel();
    m_inspiredLabel->setText("<b>Inspired by ShaderToy</b>");
    m_inspiredLabel->setAlignment(Qt::AlignCenter);
    
    m_linkOne = new QLabel();
    m_linkOne->setText("<a href=\"https://www.shadertoy.com/\">https://www.shadertoy.com/</a><br></br>");
    m_linkOne->setTextFormat(Qt::RichText);
    m_linkOne->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_linkOne->setOpenExternalLinks(true);
    m_linkOne->setAlignment(Qt::AlignCenter);

    m_contactLabel = new QLabel();
    m_contactLabel->setText("<b>Contact</b>");
    m_contactLabel->setAlignment(Qt::AlignCenter);

    m_linkTwo = new QLabel();
    m_linkTwo->setText("<a href=\"mailto:joshhhbailey@gmail.com\">joshhhbailey@gmail.com</a>");
    m_linkTwo->setTextFormat(Qt::RichText);
    m_linkTwo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_linkTwo->setOpenExternalLinks(true);
    m_linkTwo->setAlignment(Qt::AlignCenter);
}

void AboutWidget::createLayouts()
{
    QFormLayout *mainLayout = new QFormLayout();
    mainLayout->addRow(m_welcomeLabel);
    mainLayout->addRow(m_descriptionLabel);
    mainLayout->addRow(m_CETitleLabel);
    mainLayout->addRow(m_CEDescriptionLabel);
    mainLayout->addRow(m_NETitleLabel);
    mainLayout->addRow(m_NEDescriptionLabel);
    mainLayout->addRow(m_inspiredLabel);
    mainLayout->addRow(m_linkOne);
    mainLayout->addRow(m_contactLabel);
    mainLayout->addRow(m_linkTwo);
    setLayout(mainLayout);
}