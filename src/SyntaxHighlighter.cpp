///  @file SyntaxHighlighter.cpp
///  @brief Provides syntax highlighting for code editor widget

// The following code is adapted from:
// Qt., 2021. Qt Documentation - Syntax Highlighter Example [online]
// Available from: https://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html
// Accessed [22 June 2021]

#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *_parent) : QSyntaxHighlighter(_parent)
{
    // Create struct to store keyword highlighting rules
    HighlightingRule rule;

    // Interface keywords - light purple
    m_keywordsInterface.setForeground(QColor(209, 151, 217));

    const QString GLSLkeywordsInterface[] =
    {   
        QStringLiteral("\\bbreak\\b"), QStringLiteral("\\bcontinue\\b"), QStringLiteral("\\bdo\\b"),
        QStringLiteral("\\bfor\\b"), QStringLiteral("\\bwhile\\b"), QStringLiteral("\\bif\\b"),
        QStringLiteral("\\belse\\b"), QStringLiteral("\\discard\\b"), QStringLiteral("\\breturn\\b"),
        QStringLiteral("\\bswitch\\b"), QStringLiteral("\\bcase\\b"), QStringLiteral("\\bdefault\\b"),
        QStringLiteral("\\bdefine\\b")
    };

    for (const QString &pattern : GLSLkeywordsInterface)
    {
        rule.m_pattern = QRegularExpression(pattern);
        rule.m_format = m_keywordsInterface;
        m_highlightingRules.append(rule);
    }

    // Other keywords - light blue
    m_keywordsOther.setForeground(QColor(86, 156, 214));

    // The OpenGL Shading Language (v4.10)
    // https://www.khronos.org/registry/OpenGL/specs/gl/GLSLangSpec.4.10.pdf
    const QString GLSLkeywordsOther[] =
    {
        QStringLiteral("\\battribute\\b"), QStringLiteral("\\bconst\\b"), QStringLiteral("\\buniform\\b"),
        QStringLiteral("\\bvarying\\b"), QStringLiteral("\\bcentroid\\b"), QStringLiteral("\\bin\\b"),
        QStringLiteral("\\bout\\b"), QStringLiteral("\\binout\\b"), QStringLiteral("\\bfloat\\b"),
        QStringLiteral("\\bint\\b"), QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bbool\\b"),
        QStringLiteral("\\btrue\\b"), QStringLiteral("\\bfalse\\b"), QStringLiteral("\\binvariant\\b"),
        QStringLiteral("\\bmat2\\b"), QStringLiteral("\\bmat3\\b"), QStringLiteral("\\bmat4\\b"),
        QStringLiteral("\\bdmat2\\b"), QStringLiteral("\\bdmat3\\b"), QStringLiteral("\\bdmat4\\b"),
        QStringLiteral("\\bmat2x2\\b"), QStringLiteral("\\bmat2x3\\b"), QStringLiteral("\\bmat2x4\\b"),
        QStringLiteral("\\bmat3x2\\b"), QStringLiteral("\\bmat3x3\\b"), QStringLiteral("\\bmat3x4\\b"),
        QStringLiteral("\\bmat4x2\\b"), QStringLiteral("\\bmat4x3\\b"), QStringLiteral("\\bmat4x4\\b"),
        QStringLiteral("\\bdmat2x2\\b"), QStringLiteral("\\bdmat2x3\\b"), QStringLiteral("\\bdmat2x4\\b"),
        QStringLiteral("\\bdmat3x2\\b"), QStringLiteral("\\bdmat3x3\\b"), QStringLiteral("\\bdmat3x4\\b"),
        QStringLiteral("\\bdmat4x2\\b"), QStringLiteral("\\bdmat4x3\\b"), QStringLiteral("\\bdmat4x4\\b"),
        QStringLiteral("\\bvec2\\b"), QStringLiteral("\\bvec3\\b"), QStringLiteral("\\bvec4\\b"),
        QStringLiteral("\\bivec2\\b"), QStringLiteral("\\bivec3\\b"), QStringLiteral("\\bivec4\\b"),
        QStringLiteral("\\bbvec2\\b"), QStringLiteral("\\bbvec3\\b"), QStringLiteral("\\bbvec4\\b"),
        QStringLiteral("\\bdvec2\\b"), QStringLiteral("\\bdvec3\\b"), QStringLiteral("\\bdvec4\\b"),
        QStringLiteral("\\buvec2\\b"), QStringLiteral("\\buvec3\\b"), QStringLiteral("\\buvec4\\b"),
        QStringLiteral("\\bsampler1D\\b"), QStringLiteral("\\bsampler2D\\b"), QStringLiteral("\\bsampler3D\\b"),
        QStringLiteral("\\bisampler1D\\b"), QStringLiteral("\\bisampler2D\\b"), QStringLiteral("\\bisampler3D\\b"),
        QStringLiteral("\\busampler1D\\b"), QStringLiteral("\\busampler2D\\b"), QStringLiteral("\\busampler3D\\b"),
        QStringLiteral("\\bsamplerCube\\b"), QStringLiteral("\\bisamplerCube\\b"), QStringLiteral("\\busamplerCube\\b"), 
        QStringLiteral("\\bsampler1DShadow\\b"), QStringLiteral("\\bsampler2DShadow\\b"), QStringLiteral("\\bsamplerCubeShadow\\b"),
        QStringLiteral("\\bsampler1DArray\\b"), QStringLiteral("\\bsampler2DArray\\b"), QStringLiteral("\\bisampler1DArray\\b"),
        QStringLiteral("\\bisampler2DArray\\b"), QStringLiteral("\\busampler1DArray\\b"), QStringLiteral("\\busampler2DArray\\b"),
        QStringLiteral("\\bsampler1DArrayShadow\\b"), QStringLiteral("\\bsampler2DArrayShadow\\b"), QStringLiteral("\\bisampler1DArray\\b"),
        QStringLiteral("\\bisampler2DArray\\b"), QStringLiteral("\\bsampler2DRect\\b"), QStringLiteral("\\bsampler2DRectShadow\\b"),
        QStringLiteral("\\bisampler2DRect\\b"), QStringLiteral("\\busampler2DRect\\b"), QStringLiteral("\\bsampleBuffer\\b"),
        QStringLiteral("\\bisampleBuffer\\b"), QStringLiteral("\\busampleBuffer\\b"), QStringLiteral("\\bsampler2DMS\\b"),
        QStringLiteral("\\bisampler2DMS\\b"), QStringLiteral("\\busampler2DMS\\b"), QStringLiteral("\\bsampler2DMSArray\\b"),
        QStringLiteral("\\bisampler2DMSArray\\b"), QStringLiteral("\\busampler2DMSArray\\b"), QStringLiteral("\\bsamplerCubeArray\\b"),
        QStringLiteral("\\bsamplerCubeArrayShadow\\b"), QStringLiteral("\\bisamplerCubeArray\\b"), QStringLiteral("\\busamplerCubeArray\\b"),
        QStringLiteral("\\bstruct\\b"), QStringLiteral("\\blayout\\b"), QStringLiteral("\\bflat\\b"),
        QStringLiteral("\\bsmooth\\b"), QStringLiteral("\\bnoperspective\\b"), QStringLiteral("\\bpatch\\b"),
        QStringLiteral("\\bsample\\b"), QStringLiteral("\\bsubroutine\\b"), QStringLiteral("\\bdouble\\b"),
        QStringLiteral("\\blowp\\b"), QStringLiteral("\\bmediump\\b"), QStringLiteral("\\bhighp\\b"),
        QStringLiteral("\\bprecision\\b")
    };

    for (const QString &pattern : GLSLkeywordsOther)
    {
        rule.m_pattern = QRegularExpression(pattern);
        rule.m_format = m_keywordsOther;
        m_highlightingRules.append(rule);
    }

    // Single line comments - dark green
    m_singleLineCommentFormat.setForeground(QColor(96, 139, 78));
    rule.m_pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.m_format = m_singleLineCommentFormat;
    m_highlightingRules.append(rule);

    // Multi-line comments - dark green
    m_multiLineCommentFormat.setForeground(QColor(96, 139, 78));
    m_commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    m_commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));

    // Strings - orange
    m_quotationFormat.setForeground(QColor(206, 145, 120));
    rule.m_pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.m_format = m_quotationFormat;
    m_highlightingRules.append(rule);

    // Functions - yellow
    m_functionFormat.setForeground(QColor(220, 220, 170));
    rule.m_pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.m_format = m_functionFormat;
    m_highlightingRules.append(rule);

    // Numbers - light green
    /*m_numberFormat.setForeground(QColor(127, 179, 71));
    rule.m_pattern = QRegularExpression(QStringLiteral("^[+-]?\\d*\\.\\d+$|^[+-]?\\d+(\\.\\d*)?$"));
    rule.m_format = m_numberFormat;
    m_highlightingRules.append(rule);*/
}

void SyntaxHighlighter::highlightBlock(const QString &_text)
{
    // Check rules against text to see if any rules are satisfied
    for (const HighlightingRule &rule : qAsConst(m_highlightingRules))
    {
        QRegularExpressionMatchIterator matchIterator = rule.m_pattern.globalMatch(_text);
        while (matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.m_format);
        }
    }

    // All patterns checked and satisfied
    setCurrentBlockState(0);

    // Multi-line comment search
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = _text.indexOf(m_commentStartExpression);

    while (startIndex >= 0)
    {
        QRegularExpressionMatch match = m_commentEndExpression.match(_text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = _text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, m_multiLineCommentFormat);
        startIndex = _text.indexOf(m_commentStartExpression, startIndex + commentLength);
    }
}