#ifndef ASSISTFONCTIONHASARD_HPP
#define ASSISTFONCTIONHASARD_HPP

#include "ui_assistfonctionhasard.h"

class assistFonctionHasard : public QDialog, private Ui::assistFonctionHasard
{
    Q_OBJECT
protected:
    QString *valRet;
protected slots:
    void actualiseAffichage(QString);
    void actualiseAffichage();
    void valide();
    void annule();
public:
    explicit assistFonctionHasard(QWidget *parent = 0 ,QString *retour = new QString(), QList<QStringList> variables = QList<QStringList>());
    enum
    {
        Hasard = 4
    };
};

#endif // ASSISTFONCTIONHASARD_HPP
