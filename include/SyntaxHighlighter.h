/// \brief Provides syntax highlighting for code editor widget
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

// The following code is adapted from:
// Qt., 2021. Qt Documentation - Syntax Highlighter Example [online]
// Available from: https://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html
// Accessed [22 June 2021]

#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHighlighter(QTextDocument *_parent = 0);

protected:
    void highlightBlock(const QString &_text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression m_pattern;
        QTextCharFormat m_format;
    };

    QVector<HighlightingRule> m_highlightingRules;

    // Multi-line comment start and end
    QRegularExpression m_commentStartExpression;
    QRegularExpression m_commentEndExpression;

    QTextCharFormat m_keywordsInterface;
    QTextCharFormat m_keywordsOther;
    QTextCharFormat m_singleLineCommentFormat;
    QTextCharFormat m_multiLineCommentFormat;
    QTextCharFormat m_quotationFormat;
    QTextCharFormat m_functionFormat;
    QTextCharFormat m_numberFormat;
};

#endif  // _SYNTAXHIGHLIGHTER_H