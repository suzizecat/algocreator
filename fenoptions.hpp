#ifndef FENOPTIONS_HPP
#define FENOPTIONS_HPP

#include "ui_fenoptions.h"
#include <QFile>
#include <QDialog>
#include <QRegExp>
#include <QSettings>
#include <QStandardItemModel>
#include <QMessageBox>


class fenoptions : public QDialog, private Ui::fenoptions
{
    Q_OBJECT

public:
    explicit fenoptions(QWidget *parent = 0);

    static QStringList extraitParam(QString,bool=1,bool=0);


private:
    QStandardItemModel *modelRegexTable;
    QSettings param;
private slots:

    void affVar();
    void initVal();
    bool sauveParam();
    void sauveEtQuitte();
};

#endif // FENOPTIONS_HPP
