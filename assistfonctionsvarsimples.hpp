#ifndef ASSISTFONCTIONSVARSIMPLES_HPP
#define ASSISTFONCTIONSVARSIMPLES_HPP

#include "ui_assistfonctionsvarsimples.h"

class assistFonctionsVarSimples : public QDialog, private Ui::assistFonctionsVarSimples
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
    explicit assistFonctionsVarSimples(QWidget *parent = 0 ,QString *retour = new QString(), int fonction = -1, QList<QStringList> variables = QList<QStringList>());

    enum
    {
        Saisie = 2,
        Affichage = 3,
        PartieEntiere = 5
    };
};

#endif // ASSISTFONCTIONSVARSIMPLES_HPP
