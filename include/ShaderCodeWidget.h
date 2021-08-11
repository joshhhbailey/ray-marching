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
    void libraryButtonClicked();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();
    void timerEvent(QTimerEvent *_event);

    void loadLibrary();

    CodeEditor *m_codeEditor;
    SyntaxHighlighter *m_syntaxHighlighter;

    CodeEditor *m_libraryEditor;
    SyntaxHighlighter *m_libraryHighlighter;
    bool m_libraryLoaded = false;

    QLabel *m_fontSizeLabel;
    QSpinBox *m_fontSize;
    QPushButton *m_compileButton;
    QPushButton *m_pauseButton;
    QPushButton *m_libraryButton;
    QLabel *m_outputLabel;
    QLabel *m_timerLabel;

    bool m_pauseTime = false;
    qint64 m_pausedTime = 0;

    NGLScene *m_scene;
};