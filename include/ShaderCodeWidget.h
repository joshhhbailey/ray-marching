#pragma once
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
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

public slots:
    void compileButtonClicked();
    void pauseButtonClicked();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();
    void timerEvent(QTimerEvent *_event);

    CodeEditor *m_codeEditor;
    SyntaxHighlighter *m_syntaxHighlighter;
    QLabel *m_fontSizeLabel;
    QSpinBox *m_fontSize;
    QPushButton *m_compileButton;
    QPushButton *m_pauseButton;
    QLabel *m_outputLabel;
    QLabel *m_timerLabel;

    bool m_pauseTime = false;
    qint64 m_pausedTime = 0;

    NGLScene *m_scene;
};