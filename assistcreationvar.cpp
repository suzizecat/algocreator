#include "assistcreationvar.hpp"

assistCreationVar::assistCreationVar(QWidget *parent, QString *retour) :
    QDialog(parent)
{
    setupUi(this);
    valRet = retour;
    QStringList types;
    types << "Numérique" << "Chaine" << "Liste";
    typeVar->addItems(types);
    actualiseAffichage("");
    connect(typeVar,SIGNAL(currentIndexChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(nomVariable,SIGNAL(textChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(valide()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(annule()));
}
void assistCreationVar::actualiseAffichage(QString var)
{
    if(nomVariable->text() == "")
        description->setText("Vous devez entrer un nom pour votre variable");
    else
    {
        nomVariable->setText(nomVariable->text().remove("[^a-zA-Z0-9_]"));
        description->setText(QString("Vous voulez créer la VARIABLE " + nomVariable->text() + " de TYPE " + typeVar->currentText()));
    }
}

void assistCreationVar::valide()
{

    switch(typeVar->currentIndex())
    {
    case 0:
        if(nomVariable->text() != "")
            *valRet =(QString(nomVariable->text()+" est un nombre"));
        break;
    case 1:
        if(nomVariable->text() != "")
            *valRet =(QString(nomVariable->text()+" est une chaine"));
        break;
    case 2:
        if(nomVariable->text() != "")
            *valRet =(QString(nomVariable->text()+" est une liste"));
        break;
    }

   if(nomVariable->text() == "")
       annule();

    close();
}
void assistCreationVar::annule()
{
    *valRet =(QString(""));
    close();
}
