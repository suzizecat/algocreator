#include "assistfonctionsvarsimples.hpp"

assistFonctionsVarSimples::assistFonctionsVarSimples(QWidget *parent,QString *retour, int fonction, QList<QStringList> variables) :
    QDialog(parent)
{
    setupUi(this);
    valRet = retour;
    fct = fonction;
    QString texte;
    texte = "Bienvenue dans l'assistant à la saisie d'algorithmes d'AlgoCreator\n";
    switch (fonction)
    {
    case Saisie:
        texte += "Choisissez dans la liste ci-dessous la variable dont l'utilisateur devra saisir la valeur.";
        break;
    case Affichage:
        texte += "Choisissez dans la liste ci-dessous la variable qu'AlgoCreator devra afficher.";
        break;
    case PartieEntiere:
       texte += "Choisissez dans la liste ci-dessous la variable dont vous voulez extraire la partie entière.";
       break;
    default:
        texte += "Erreur : La fonction n'a pas été appelée correctement.\nMerci d'envoyer un mail contenant votre algorithme et une description de l'erreur à \nwebmaster@amidemoi.com\nCode : DIAL_FCTSIMPLE INT_FCT_INVALIDE :" + fonction;
        break;
    }

    message->setText(texte);

    switch (fonction)
    {
    case Saisie:
        listeVar->addItems(variables[0]);
        listeVar->addItems(variables[1]);
        break;
    case Affichage:
        listeVar->addItems(variables[0]);
        listeVar->addItems(variables[1]);
        listeVar->addItems(variables[2]);
        break;
    case PartieEntiere:
        listeVar->addItems(variables[0]);
    }
    actualiseAffichage(listeVar->currentText());
    connect(listeVar,SIGNAL(currentIndexChanged(QString)),this,SLOT(actualiseAffichage(QString)));
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(valide()));
    connect(buttonBox,SIGNAL(rejected()),this,SLOT(annule()));
}

void assistFonctionsVarSimples::actualiseAffichage(QString var)
{
    switch (fct)
    {
    case Saisie:
        descriptif->setText(QString("Vous demandez à l'utilisateur de SAISIR la valeur de " + var));
        break;
    case Affichage:
        descriptif->setText(QString("Vous demandez à AlgoCreator d'AFFICHER la valeur de " + var));
        break;
    case PartieEntiere:
        descriptif->setText(QString("Vous demandez à AlgoCreator la PARTIE ENTIÈRE de " + var));
    default:
        descriptif->setText(QString("Une erreur est survenue (cf texte ci-dessus)"));
        break;
    }
    variable = var;
}

void assistFonctionsVarSimples::valide()
{
    switch (fct)
    {
    case Saisie:
        *valRet =(QString("SAISIR " + variable));
        break;
    case Affichage:
        *valRet =(QString("AFFICHER " + variable));
        break;
    case PartieEntiere:
        *valRet =(QString("PART_ENT " + variable));
        break;
    default:
       *valRet =(QString("ERR"));
        break;
    }
    close();
}
void assistFonctionsVarSimples::annule()
{
     *valRet =(QString(""));
      close();
}
