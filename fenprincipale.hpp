#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QMainWindow>
#include <QList>
#include <QFileDialog>
#include <QPrintDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QButtonGroup>


#include <Qsci/qsciapis.h>
#include <Qsci/qsciprinter.h>
#include <Qsci/qscilexercpp.h>
#include "qscilexeralgo.hpp"

#include "fenoptions.hpp"
#include "ui_fenprincipale.h"
#include "assistcreationvar.hpp"
#include "assistfonctionsvarsimples.hpp"
#include "assistfonctionsconditions.hpp"
#include "assistfonctionhasard.hpp"



class FenPrincipale : public QMainWindow, private Ui::FenPrincipale
{
    Q_OBJECT

public:
    FenPrincipale(QMainWindow *parent = 0);


protected:

    QButtonGroup *btnsSaiAssist;
    QString nom_fichier;
    QString chemin_fichier;


    QString def_rxVariable; //Bout de Regex : un nom de variable
    QString def_rxValListe; //Bout de Regex : valeur d'un indice dans une liste
    QString def_rxNombre;
    QString def_rxOp;
    QStringList paramVal;
    QStringList paramVar;

    QRegExp rxLigne; //Regex : une ligne de texte
    QRegExp rxNbVar; //Regex : déclaration / affectation d'une variable de type NOMBRE
    QRegExp rxTxVar; //Regex : déclaration / affectation d'une variable de type CHAÎNE
    QRegExp rxLsVar; //Regex : déclaration d'une variable de type LISTE


    QStringList NbVar; //Liste des noms de variables de type nombre
    QStringList TxVar; //Liste des noms de variables de type texte
    QStringList LsVar; //Liste des noms de variables de type liste

    QList<QVariant> NbVal;          //Valeurs des variables de type nombre
    QList<QList<QVariant> > LsVal;  //Valeurs des variables de type liste
    QStringList TxVal;              //Valeurs des variables de type texte


    QStringList ActFinales; //Actions à executer [Action](Type de var)<pos de la modif>var=val
    QStringList Lignes;     //Lignes d'actions à executer

    QRegExp rxVarOpSurSoisMeme; //Regex : Opération par raccourcis
    QRegExp rxModifListe;       //Regex : Modification d'une liste
    QRegExp rxRecupValListe;    //Regex : Récupération d'une valeur d'une liste
    QRegExp rxRecupSaisie;
    QRegExp rxAfficheVar;       //Regex : Affichage de la valeur d'une variable
    QRegExp rxCondition;        //Regex : Definition d'une condition
    QRegExp rxBoucle;           //Regex : Définition d'une boucle type <while ...>
    QRegExp rxBoucle2;          //Regex : Definition d'une boucle type <do ... while>

    QRegExp rxValAlea;          //Regex : Remplacement de cette regex par un nombre aleatoire
    QRegExp rxValEnt;

    bool dansBoucle2;

    QString retirerGuillemets(QString);
    QString execOp(QString);

    bool defVarNb(QString);
    bool defVarTx(QString);
    bool defVarLs(QString);

    bool modSaisie(QString);

    bool modVarOpSurSoisMeme(QString);
    bool modListe(QString, bool=true);
    bool modListe(QString,int=0 , QVariant = QVariant(), bool=true);

    bool affVal(QString);

    QVariant recupValListe(QString);


    int execCondition(QString);
    int execBoucle(QString);


 public slots :
    void tester(bool executer = true);
    void affOptions();
    void sauvegarder();
    void imprimer();
    void ouvrir();
    void nouveau();
    void affSaiAssistee(bool=true);
    void assisteSaisie(int);
};

#endif // FENRINCIPALE_H
