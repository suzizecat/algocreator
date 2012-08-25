#include "assistfonctionhasard.hpp"

assistFonctionHasard::assistFonctionHasard(QWidget *parent ,QString *retour, QList<QStringList> variables):
    QDialog(parent)
{
    setupUi(this);
    valRet = retour;

    listeVar->addItem("");
    listeVar->addItems(variables[0]);

    actualiseAffichage("");
    connect(listeVar,SIGNAL(currentIndexChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(valDecimale,SIGNAL(clicked()),this,SLOT(actualiseAffichage()));
    connect(valEntiere,SIGNAL(clicked()),this,SLOT(actualiseAffichage()));
    connect(valMin,SIGNAL(valueChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(valMax,SIGNAL(valueChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(valide()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(annule()));
}
void assistFonctionHasard::actualiseAffichage()
{
    actualiseAffichage("");
}

void assistFonctionHasard::actualiseAffichage(QString var)
{
    QString info;
    if(valMin->value() > valMax->value())
    {
        valMax->setValue(valMin->value()+1);
    }

    valMin->setEnabled(valEntiere->isChecked());
    valMax->setEnabled(valEntiere->isChecked());

    if (listeVar->currentText() == "")
        info = "Vous voulez génerer une valeur ALEATOIRE ";
    else
        info = "Vous voulez que la variable " + listeVar->currentText() + " prenne une valeur ALEATOIRE ";
    if(valDecimale->isChecked())
        info += " décimale entre 0 et 1";
    else
        info += " entière entre " + QVariant(valMin->value()).toString() + " et " + QVariant(valMax->value()).toString();

    description->setText(info);

}

void assistFonctionHasard::valide()
{
    QString res;

    if (listeVar->currentText() != "")
        res = listeVar->currentText() +" = ";

    res+= "HASARD ";

    if(valEntiere->isChecked())
    {
        if (valMin->value()==0)
            res += QVariant(valMax->value()).toString();
        else
            res += QVariant(valMin->value()).toString() + "," + QVariant(valMax->value()).toString();
    }

     *valRet = res;
    close();

    }

void assistFonctionHasard::annule()
{
    *valRet =(QString(""));
    close();
}
