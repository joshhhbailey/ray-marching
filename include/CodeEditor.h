/// \brief Creates a code editor widget
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

// The following code is adapted from:
// Qt., 2021. Qt Documentation - Code Editor Example [online]
// Available from: https://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
// Accessed [17 June 2021]

#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    CodeEditor();
    void lineNumberAreaPaintEvent(QPaintEvent *_event);
    int lineNumberAreaWidth();
    
    QString getShaderCode() { return toPlainText(); }
    void setShaderCode(QString _code) { setPlainText(_code); }

    void reset();

public slots:
    void setFontSize(int _size);

protected:
    void resizeEvent(QResizeEvent *_event) override;

private slots:
    void updateLineNumberAreaWidth();
    void updateLineNumberArea(const QRect &_rect, int _dy);

private:
    void updateFont();

    QWidget *m_lineNumberArea;

    // Font settings
    QString m_fontName = "Consolas";
    int m_fontSize = 11;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *_editor) : QWidget(_editor), m_codeEditor(_editor)
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
    CodeEditor *m_codeEditor;
};

#endif  // _CODEEDITOR_H