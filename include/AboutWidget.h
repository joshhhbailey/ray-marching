#pragma once

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>

class AboutWidget : public QGroupBox
{
    Q_OBJECT
public:
    AboutWidget();

private:
    void createWidgets();
    void createLayouts();

    QLabel *m_welcomeLabel;
    QLabel *m_descriptionLabel;
    QLabel *m_CETitleLabel;
    QLabel *m_CEDescriptionLabel;
    QLabel *m_NETitleLabel;
    QLabel *m_NEDescriptionLabel;
    QLabel *m_inspiredLabel;
    QLabel *m_linkOne;
    QLabel *m_contactLabel;
    QLabel *m_linkTwo;
};