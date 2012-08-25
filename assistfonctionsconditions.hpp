#ifndef ASSISTFONCTIONSCONDITIONS_HPP
#define ASSISTFONCTIONSCONDITIONS_HPP

#include "ui_assistfonctionsconditions.h"

class assistFonctionsConditions : public QDialog, private Ui::assistFonctionsConditions
{
    Q_OBJECT
protected:
    int fct;
    QString variable;
    QString *valRet;

protected slots:
    void actualiseAffichage(QString);
    void valide();
    void annule();
public:
    explicit assistFonctionsConditions(QWidget *parent = 0 ,QString *retour = new QString(), int fonction = -1, QList<QStringList> variables = QList<QStringList>());

    enum
    {
        ConditionSimple = 6,
        ConditionComplexe = 7,
        Boucle1 = 8,
        Boucle2 = 9
    };
};

#endif // ASSISTFONCTIONSCONDITIONS_HPP
