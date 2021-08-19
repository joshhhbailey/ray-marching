/// \brief Creates 'About' window
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef ABOUTWIDGET_H_
#define ABOUTWIDGET_H_

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

#endif   // _ABOUTWIDGET_H_