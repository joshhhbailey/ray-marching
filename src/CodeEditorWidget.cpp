// The following code is adapted from:
// Qt., 2021. Qt Documentation - Code Editor Example [online]
// Available from: https://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
// Accessed [17 June 2021]

#include "CodeEditorWidget.h"

#include <QPainter>
#include <QTextBlock>

CodeEditorWidget::CodeEditorWidget() : QPlainTextEdit()
{
    m_lineNumberArea = new LineNumberArea(this);

    // Text edit settings
    QFont font(m_fontName, m_fontSize);
    setFont(font);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setTabStopDistance(m_fontSize * 2);

    // Stretch text editor to bottom of window
    QSizePolicy policy = sizePolicy();
    policy.setVerticalStretch(1);
    setSizePolicy(policy);

    // Default code when app launches
    const char code[] =
    "void main()\n"
    "{\n"
	"   fragColour = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "}";

    setPlainText(code);

    // Initialise line number area width and highlight first line
    connect(this, &CodeEditorWidget::blockCountChanged, this, &CodeEditorWidget::updateLineNumberAreaWidth);
    connect(this, &CodeEditorWidget::updateRequest, this, &CodeEditorWidget::updateLineNumberArea);

    updateLineNumberAreaWidth();
}

int CodeEditorWidget::lineNumberAreaWidth()
{
    int digits = 1;                     // Maximum line number digits
    int max = qMax(1, blockCount());    // Maximum line number

    // For everyone power of 10, increment digits
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }

    int space = 10 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

QString CodeEditorWidget::retrieveShaderCode()
{
    return this->toPlainText();
}

void CodeEditorWidget::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditorWidget::updateLineNumberArea(const QRect &_rect, int _dy)
{
    // Scroll line numbers
    if (_dy)
    {
        m_lineNumberArea->scroll(0, _dy);
    }
    else
    {
        m_lineNumberArea->update(0, _rect.y(), m_lineNumberArea->width(), _rect.height());
    }

    if (_rect.contains(viewport()->rect()))
    {
        updateLineNumberAreaWidth();
    }
}

void CodeEditorWidget::resizeEvent(QResizeEvent *_e)
{
    // When editor changes size, resize line number area
    QPlainTextEdit::resizeEvent(_e);

    QRect cr = contentsRect();
    m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditorWidget::lineNumberAreaPaintEvent(QPaintEvent *_event)
{
    // Paint margin background
    QPainter painter(m_lineNumberArea);
    painter.fillRect(_event->rect(), Qt::lightGray);

    // Loop visible lines and paint line numbers
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= _event->rect().bottom())
    {
        if (block.isVisible() && bottom >= _event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, m_lineNumberArea->width(), fontMetrics().height(), Qt::AlignCenter, number);
        }
        
        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}