// The following code is adapted from:
// Qt., 2021. Qt Documentation - Code Editor Example [online]
// Available from: https://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
// Accessed [17 June 2021]

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

class CodeEditorWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    CodeEditorWidget();
    void lineNumberAreaPaintEvent(QPaintEvent *_event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *_event) override;

private slots:
    void updateLineNumberAreaWidth();
    void updateLineNumberArea(const QRect &_rect, int _dy);

private:
    QWidget *m_lineNumberArea;

    // Font settings
    QString m_fontName = "Consolas";
    int m_fontSize = 11;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditorWidget *_editor) : QWidget(_editor), m_codeEditor(_editor)
    {}

    QSize sizeHint() const override
    {
        return QSize(m_codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        m_codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditorWidget *m_codeEditor;
};

#endif