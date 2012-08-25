#ifndef ASSISTCREATIONVAR_HPP
#define ASSISTCREATIONVAR_HPP

#include "ui_assistcreationvar.h"

class assistCreationVar : public QDialog, private Ui::assistCreationVar
{
    Q_OBJECT
protected:
    QString *valRet;
protected slots:
    void actualiseAffichage(QString);
    void valide();
    void annule();
public:
    explicit assistCreationVar(QWidget *parent = 0, QString *retour = new QString());

    enum
    {
        CreationVariable = 1
    };
};

#endif // ASSISTCREATIONVAR_HPP
