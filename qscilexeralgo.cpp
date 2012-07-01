// This module implements the QsciLexerAlgo class.
//
// Copyright (c) 2010 Riverbank Computing Limited <info@riverbankcomputing.com>
//
// This file is part of QScintilla.
//
// This file may be used under the terms of the GNU General Public
// License versions 2.0 or 3.0 as published by the Free Software
// Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
// included in the packaging of this file.  Alternatively you may (at
// your option) use any later version of the GNU General Public
// License if such license has been publicly approved by Riverbank
// Computing Limited (or its successors, if any) and the KDE Free Qt
// Foundation. In addition, as a special exception, Riverbank gives you
// certain additional rights. These rights are described in the Riverbank
// GPL Exception version 1.1, which can be found in the file
// GPL_EXCEPTION.txt in this package.
//
// Please review the following information to ensure GNU General
// Public Licensing requirements will be met:
// http://trolltech.com/products/qt/licenses/licensing/opensource/. If
// you are unsure which license is appropriate for your use, please
// review the following information:
// http://trolltech.com/products/qt/licenses/licensing/licensingoverview
// or contact the sales department at sales@riverbankcomputing.com.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


#include "qscilexeralgo.hpp"

#include <qcolor.h>
#include <qfont.h>
#include <qsettings.h>


// The ctor.
QsciLexerAlgo::QsciLexerAlgo(QObject *parent, bool caseInsensitiveKeywords)
    : QsciLexer(parent),
      fold_atelse(false), fold_comments(false), fold_compact(true),
      fold_preproc(true), style_preproc(false), dollars(true),
      nocase(caseInsensitiveKeywords)
{
}


// The dtor.
QsciLexerAlgo::~QsciLexerAlgo()
{
}


// Returns the language name.
const char *QsciLexerAlgo::language() const
{
    return "C++";
}


// Returns the lexer name.
const char *QsciLexerAlgo::lexer() const
{
    return (nocase ? "cppnocase" : "cpp");
}



// Return the set of character sequences that can separate auto-completion
// words.
QStringList QsciLexerAlgo::autoCompletionWordSeparators() const
{
    QStringList wl;

    wl << " " << "_";

    return wl;
}


// Return the list of keywords that can start a block.
const char *QsciLexerAlgo::blockStartKeyword(int *style) const
{
    if (style)
        *style = Identifier;

    return "SI REPETER TANT QUE TANTQUE";
           //"protected public struct try union while";
}


// Return the list of characters that can start a block.
const char *QsciLexerAlgo::blockStart(int *style) const
{
    if (style)
        *style = Operator;

    return " ";
}


// Return the list of characters that can end a block.
const char *QsciLexerAlgo::blockEnd(int *style) const
{
    if (style)
        *style = Operator;

    return " ";
}


// Return the style used for braces.
int QsciLexerAlgo::braceStyle() const
{
    return Operator;
}


// Return the string of characters that comprise a word.
const char *QsciLexerAlgo::wordCharacters() const
{
    return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_#";
}


// Returns the foreground colour of the text for a style.
QColor QsciLexerAlgo::defaultColor(int style) const
{
    switch (style)
    {
    case Default:
        return QColor(0x80,0x80,0x80);

    case Comment:
    case CommentLine:
        return QColor(0x16,0x61,0x00);

    case CommentDoc:
    case CommentLineDoc:
        return QColor(0x3f,0x70,0x3f);

    case Number:
        return QColor(0x00,0x7f,0x7f);

    case Keyword:
        return QColor(0x00,0x00,0x7f);

    case DoubleQuotedString:
    case SingleQuotedString:
        return QColor(0x7f,0x00,0x7f);

    case PreProcessor:
        return QColor(0x7f,0x7f,0x00);

    case Operator:
    case UnclosedString:
        return QColor(0x3d,0x00,0x00);

    case Identifier:
        return QColor(0x0e,0x53,0x56);
        break;

    case Regex:
        return QColor(0x0f,0x46,0x0c);

    case CommentDocKeyword:
        return QColor(0x30,0x60,0xa0);

    case CommentDocKeywordError:
        return QColor(0x80,0x40,0x20);
    }

    return QsciLexer::defaultColor(style);
}


// Returns the end-of-line fill for a style.
bool QsciLexerAlgo::defaultEolFill(int style) const
{
    if (style == UnclosedString)
        return true;

    return QsciLexer::defaultEolFill(style);
}


// Returns the font of the text for a style.
QFont QsciLexerAlgo::defaultFont(int style) const
{
    QFont f;

    switch (style)
    {
    case Comment:
    case CommentLine:
    case CommentDoc:
    case CommentLineDoc:
    case CommentDocKeyword:
    case CommentDocKeywordError:
#if defined(Q_OS_WIN)
        f = QFont("Comic Sans MS",9);
#else
        f = QFont("Bitstream Vera Serif",9);
#endif
        break;

    case Keyword:
    case Operator:
        f = QsciLexer::defaultFont(style);
        f.setBold(true);
        break;

    case DoubleQuotedString:
    case SingleQuotedString:
    case UnclosedString:
#if defined(Q_OS_WIN)
        f = QFont("Courier New",10);
#else
        f = QFont("Bitstream Vera Sans Mono",9);
#endif
        break;

    default:
        f = QsciLexer::defaultFont(style);
    }

    return f;
}


// Returns the set of keywords.
const char *QsciLexerAlgo::keywords(int set) const
{
    if (set == 1)
        return
            "SAISIR << est_un_nombre  "
            "est_un_nombre est_une_chaine est une_liste nombre chaine liste est un une"
            "SI REPETER TANT QUE TANTQUE"
            "!= <= >= == < >";


    if (set == 3)
        return 0;


    return 0;
}


// Returns the user name of a style.
QString QsciLexerAlgo::description(int style) const
{
    switch (style)
    {
    case Default:
        return tr("Default");

    case Comment:
        return tr("C comment");

    case CommentLine:
        return tr("C++ comment");

    case CommentDoc:
        return tr("JavaDoc style C comment");

    case Number:
        return tr("Number");

    case Keyword:
        return tr("Keyword");

    case DoubleQuotedString:
        return tr("Double-quoted string");

    case SingleQuotedString:
        return tr("Single-quoted string");

    case UUID:
        return tr("IDL UUID");

    case PreProcessor:
        return tr("Pre-processor block");

    case Operator:
        return tr("Operator");

    case Identifier:
        return tr("Identifier");

    case UnclosedString:
        return tr("Unclosed string");

    case CommentLineDoc:
        return tr("JavaDoc style C++ comment");

    case KeywordSet2:
        return tr("Secondary keywords and identifiers");

    case CommentDocKeyword:
        return tr("JavaDoc keyword");

    case CommentDocKeywordError:
        return tr("JavaDoc keyword error");

    case GlobalClass:
        return tr("Global classes and typedefs");
    }

    return QString();
}


// Returns the background colour of the text for a style.
QColor QsciLexerAlgo::defaultPaper(int style) const
{
    if (style == UnclosedString)
        return QColor(0xe0,0xc0,0xe0);

    return QsciLexer::defaultPaper(style);
}


// Refresh all properties.
void QsciLexerAlgo::refreshProperties()
{
    setAtElseProp();
    setCommentProp();
    setCompactProp();
    setPreprocProp();
    setStylePreprocProp();
    setDollarsProp();
}


// Read properties from the settings.
bool QsciLexerAlgo::readProperties(QSettings &qs,const QString &prefix)
{
    int rc = true;

    fold_atelse = qs.value(prefix + "foldatelse", false).toBool();
    fold_comments = qs.value(prefix + "foldcomments", false).toBool();
    fold_compact = qs.value(prefix + "foldcompact", true).toBool();
    fold_preproc = qs.value(prefix + "foldpreprocessor", true).toBool();
    style_preproc = qs.value(prefix + "stylepreprocessor", false).toBool();
    dollars = qs.value(prefix + "dollars", true).toBool();

    return rc;
}


// Write properties to the settings.
bool QsciLexerAlgo::writeProperties(QSettings &qs,const QString &prefix) const
{
    int rc = true;

    qs.setValue(prefix + "foldatelse", fold_atelse);
    qs.setValue(prefix + "foldcomments", fold_comments);
    qs.setValue(prefix + "foldcompact", fold_compact);
    qs.setValue(prefix + "foldpreprocessor", fold_preproc);
    qs.setValue(prefix + "stylepreprocessor", style_preproc);
    qs.setValue(prefix + "dollars", dollars);

    return rc;
}


// Return true if else can be folded.
bool QsciLexerAlgo::foldAtElse() const
{
    return fold_atelse;
}


// Set if else can be folded.
void QsciLexerAlgo::setFoldAtElse(bool fold)
{
    fold_atelse = fold;

    setAtElseProp();
}


// Set the "fold.at.else" property.
void QsciLexerAlgo::setAtElseProp()
{
    emit propertyChanged("fold.at.else",(fold_atelse ? "1" : "0"));
}


// Return true if comments can be folded.
bool QsciLexerAlgo::foldComments() const
{
    return fold_comments;
}


// Set if comments can be folded.
void QsciLexerAlgo::setFoldComments(bool fold)
{
    fold_comments = fold;

    setCommentProp();
}


// Set the "fold.comment" property.
void QsciLexerAlgo::setCommentProp()
{
    emit propertyChanged("fold.comment",(fold_comments ? "1" : "0"));
}


// Return true if folds are compact.
bool QsciLexerAlgo::foldCompact() const
{
    return fold_compact;
}


// Set if folds are compact
void QsciLexerAlgo::setFoldCompact(bool fold)
{
    fold_compact = fold;

    setCompactProp();
}


// Set the "fold.compact" property.
void QsciLexerAlgo::setCompactProp()
{
    emit propertyChanged("fold.compact",(fold_compact ? "1" : "0"));
}


// Return true if preprocessor blocks can be folded.
bool QsciLexerAlgo::foldPreprocessor() const
{
    return fold_preproc;
}


// Set if preprocessor blocks can be folded.
void QsciLexerAlgo::setFoldPreprocessor(bool fold)
{
    fold_preproc = fold;

    setPreprocProp();
}


// Set the "fold.preprocessor" property.
void QsciLexerAlgo::setPreprocProp()
{
    emit propertyChanged("fold.preprocessor",(fold_preproc ? "1" : "0"));
}


// Return true if preprocessor lines are styled.
bool QsciLexerAlgo::stylePreprocessor() const
{
    return style_preproc;
}


// Set if preprocessor lines are styled.
void QsciLexerAlgo::setStylePreprocessor(bool style)
{
    style_preproc = style;

    setStylePreprocProp();
}


// Set the "styling.within.preprocessor" property.
void QsciLexerAlgo::setStylePreprocProp()
{
    emit propertyChanged("styling.within.preprocessor",(style_preproc ? "1" : "0"));
}


// Return true if '$' characters are allowed.
bool QsciLexerAlgo::dollarsAllowed() const
{
    return dollars;
}


// Set if '$' characters are allowed.
void QsciLexerAlgo::setDollarsAllowed(bool allowed)
{
    dollars = allowed;

    setDollarsProp();
}


// Set the "lexer.cpp.allow.dollars" property.
void QsciLexerAlgo::setDollarsProp()
{
    emit propertyChanged("lexer.cpp.allow.dollars",(dollars ? "1" : "0"));
}
