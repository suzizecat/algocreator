#include "assistfonctionsconditions.hpp"

assistFonctionsConditions::assistFonctionsConditions(QWidget *parent,QString *retour, int fonction, QList<QStringList> variables) :
    QDialog(parent)
{
    setupUi(this);
    valRet = retour;
    fct = fonction;
    QString texte;
    texte = "Bienvenue dans l'assistant à la saisie d'algorithmes d'AlgoCreator\n";
    switch (fonction)
    {
    case ConditionSimple:
        texte += "Décrivez, à l'aide des champs ci-dessous, le test qu'AlgoCreator devra effectuer pour une condition simple";
        break;
    case ConditionComplexe:
        texte += "Décrivez, à l'aide des champs ci-dessous, le test qu'AlgoCreator devra effectuer pour une condition complexe";
        break;
    case Boucle1:
        texte += "Décrivez, à l'aide des champs ci-dessous, le test qu'AlgoCreator devra effectuer pour une boucle type TANT QUE ...";
        break;
    case Boucle2:
        texte += "Décrivez, à l'aide des champs ci-dessous, le test qu'AlgoCreator devra effectuer pour une boucle type REPETER";
        break;
    default:
        texte += "Erreur : La fonction n'a pas été appelée correctement.\nMerci d'envoyer un mail contenant votre algorithme et une description de l'erreur à \nwebmaster@amidemoi.com\nCode : DIAL_FCTSIMPLE INT_FCT_INVALIDE :" + fonction;
        break;
    }

    message->setText(texte);
    QStringList signes ;
    signes << "==" << "!=" << "<=" << ">=" << "<" << ">";
    listeTest->addItems(signes);

    listeVar1->addItems(variables[0]);
    listeVar1->addItems(variables[1]);
    listeVar1->addItem("Autre");

    listeVar2->addItems(variables[0]);
    listeVar2->addItems(variables[1]);
    listeVar2->addItem("Autre");

    connect(listeVar1,SIGNAL(currentIndexChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(listeVar2,SIGNAL(currentIndexChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(saisieVar1,SIGNAL(textChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(saisieVar2,SIGNAL(textChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(listeTest,SIGNAL(currentIndexChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(valide()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(annule()));

    actualiseAffichage("");


}

void assistFonctionsConditions::actualiseAffichage(QString var)
{
    if(listeVar1->currentText() == "Autre")
    {
        var = saisieVar1->text();
        saisieVar1->setVisible(true);
    }
    else
    {
        var = listeVar1->currentText();
        saisieVar1->setVisible(false);
    }

    var += " " + listeTest->currentText() + " ";

    if(listeVar2->currentText() == "Autre")
    {
        var += saisieVar2->text();
        saisieVar2->setVisible(true);
    }
    else
    {
        var += listeVar2->currentText();
        saisieVar2->setVisible(false);
    }


    switch (fct)
    {
    case ConditionSimple:
        descriptif->setText(QString("Vous voulez executer une action SI " + var));
        break;
    case ConditionComplexe:
        descriptif->setText(QString("Vous voulez executer une action SI " + var +" et en executer une autre SINON"));
        break;
    case Boucle1:
        descriptif->setText(QString("Vous voulez executer une action TANTQUE " + var ));
        break;
    case Boucle2:
        descriptif->setText(QString("Vous voulez REPETER une action JUSQU'A CE QUE " + var ));
        break;
    default:
        descriptif->setText(QString("Une erreur est survenue (cf texte ci-dessus)"));
        break;
    }
    variable = var;
}

void assistFonctionsConditions::valide()
{
    switch (fct)
    {
    case ConditionSimple:
        *valRet =(QString("SI " + variable + " ALORS\n\t...\nFIN"));
        break;
    case ConditionComplexe:
        *valRet =(QString("SI " + variable + " ALORS\n\t...\nSINON\n\t...\nFIN"));
        break;
    case Boucle1:
        *valRet =(QString("TANT QUE " + variable + " FAIRE\n\t...\nFIN"));
        break;
    case Boucle2:
        *valRet =(QString("REPETER\n\t...\n\tJUSQU'A CE QUE " + variable + " \nFIN"));
        break;
    default:
        *valRet =(QString("ERR"));
        break;
    }
    close();
}
void assistFonctionsConditions::annule()
{
    *valRet =(QString(""));
    close();
}
