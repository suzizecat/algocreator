#include "fenprincipale.hpp"

#include "ui_fenprincipale.h"

FenPrincipale::FenPrincipale(QMainWindow *parent) : QMainWindow(parent)
{
    setupUi(this);

    qDebug() << "\nRécuperation des parametres...";
    QSettings param ;

    if( param.value("premOuverture",true) == true || param.value("version","0") != QCoreApplication::applicationVersion() )
    {
        qDebug() << "Initialisation des parametres ...";
        param.beginGroup("rxLang");
        param.setValue("rxLigne","([^\n]+)");
        param.setValue("rxVarNb","([a-zA-Z]{1}[a-zA-Z0-9_]*)(?: ?= ?([()0-9+\\-/.,*a-zA-Z _]+|([a-zA-Z]{1}[a-zA-Z0-9_]*) ?\\[([()0-9+\\-/.,*a-zA-Z _]+)\\])| est[ _]un[ _]nombre)");
        param.setValue("rxVarTx","([a-zA-Z]{1}[a-zA-Z0-9_]*)(?: ?= ?((?:\"[^\"]*\"|[a-zA-Z]{1}[a-zA-Z0-9_]*)(?: ?\\+ ?(?:\"[^\"]*\"|[a-zA-Z]{1}[a-zA-Z0-9_]*))*)+| est[ _]une[ _]cha[îi]ne)");
        param.setValue("rxVarLs","([a-zA-Z]{1}[a-zA-Z0-9_]*)(?: est[ _]une[ _]liste ?| ?\\[ ?\\])");
        param.setValue("rxModLs","([a-zA-Z]{1}[a-zA-Z0-9_]*) ?\\[([()0-9+\\-/.*a-zA-Z_]+)\\] ?= ?([^\n]+)");
        param.setValue("rxModOpSMM","([a-zA-Z]{1}[a-zA-Z0-9_]*) ?(\\<\\<|\\+=|-=|/=|\\*=|%=|\\+\\+|--) ?([()0-9+\\-/.,*a-zA-Z_ ]+|\"[^\"]*\")?");
        param.setValue("rxRecValLs","([a-zA-Z]{1}[a-zA-Z0-9_]*) ?\\[\\]");
        param.setValue("rxRecSai","SAISIR ([a-zA-Z]{1}[a-zA-Z0-9_]*) ?(?:\\[([()0-9+\\-/.*a-zA-Z_]+)\\])?");
        param.setValue("rxAffVar","AFFICHER ([a-zA-Z]{1}[a-zA-Z0-9_]*) ?(?:\\[([()0-9+\\-/.*a-zA-Z_]+)\\])?");
        param.setValue("rxValAlea","HASARD( [()0-9+\\-/.*a-zA-Z_]+)?(?: ?,([()0-9+\\-/.*a-zA-Z_]+))?");
        param.setValue("rxValEnt","PART_ENT( [()0-9+\\-/.*a-zA-Z_]+)?");
        param.setValue("rxStrCondition","SI ([a-zA-Z]{1}[a-zA-Z0-9_]*|([a-zA-Z]{1}[a-zA-Z0-9_]*) ?\\[([()0-9+\\-/.*a-zA-Z_]+)\\]) ?(\\<|==|\\<=|\\>=|\\>|!=) ?([()0-9+\\-/.*a-zA-Z_]+|[a-zA-Z]{1}[a-zA-Z0-9_]*|([a-zA-Z]{1}[a-zA-Z0-9_]*) ?\\[([()0-9+\\-/.*a-zA-Z_]+)\\]|\"[^\"]*\") ALORS");
        param.setValue("rxStrBoucle","TANT ?QUE ([a-zA-Z]{1}[a-zA-Z0-9_]*|([a-zA-Z]{1}[a-zA-Z0-9_]*) ?\\[([()0-9+\\-/.*a-zA-Z_]+)\\]) ?(\\<|==|\\<=|\\>=|\\>|!=) ?([()0-9+\\-/.*a-zA-Z_]+|[a-zA-Z]{1}[a-zA-Z0-9_]*([a-zA-Z]{1}[a-zA-Z0-9_]*) ?\\[([()0-9+\\-/.*a-zA-Z_]+)\\]|\"[^\"]*\") FAIRE");
        param.setValue("rxStrBoucle2", "JUSQU[' ]?A CE QUE ([a-zA-Z]{1}[a-zA-Z0-9_]*|([a-zA-Z]{1}[a-zA-Z0-9_]*) ?\\[([()0-9+\\-/.*a-zA-Z_]+)\\]) ?(\\<|==|\\<=|\\>=|\\>|!=) ?([()0-9+\\-/.*a-zA-Z_]+|[a-zA-Z]{1}[a-zA-Z0-9_]*([a-zA-Z]{1}[a-zA-Z0-9_]*) ?\\[([()0-9+\\-/.*a-zA-Z_]+)\\]|\"[^\"]*\")");

        param.endGroup();

        if( param.value("premOuverture",true).toBool())
        {
            info(this,"Bienvenue dans AlgoCreator version "+QCoreApplication::applicationVersion()+" !");
        }
        else
        {
            info(this,"Bienvenue dans AlgoCreator !\nLa mise à jour de la version "+param.value("version","0").toString()+" à la version "+ QCoreApplication::applicationVersion() +" s'est correctement effectuée...");
        }

        param.setValue("premOuverture",false);
        param.setValue("version",QCoreApplication::applicationVersion());
    }

    qDebug() << "Definition des variables...";

    def_rxVariable = "[a-zA-Z]{1}[a-zA-Z0-9_]*";
    def_rxNombre = "-?\\d+(?:\\.|,)?\\d*";
    def_rxOp = "[()0-9+\\-/.*a-zA-Z_]+";
    def_rxValListe = "("+def_rxVariable+") ?\\[([()0-9+\\-/.*a-zA-Z_]+)\\]";


    nom_fichier = "Sans Titre";
    chemin_fichier = "";

    param.beginGroup("rxLang");

    qDebug() << "Initialisation des regexs ...";

    rxLigne = QRegExp(param.value("rxLigne").toString());
    //Definition de la déclaration d'un nombre
    rxNbVar =  QRegExp(param.value("rxVarNb").toString());
    //Definition de la déclaration d'une chaîne
    rxTxVar = QRegExp(param.value("rxVarTx").toString());
    //Définition de la déclaration d'une liste
    rxLsVar = QRegExp(param.value("rxVarLs").toString());


    rxModifListe = QRegExp(param.value("rxModLs").toString());
    rxRecupValListe = QRegExp(param.value("rxRecValLs").toString());
    rxRecupSaisie = QRegExp(param.value("rxRecSai").toString());
    rxAfficheVar = QRegExp(param.value("rxAffVar").toString());
    rxVarOpSurSoisMeme = QRegExp(param.value("rxModOpSMM").toString());
    rxCondition = QRegExp(param.value("rxStrCondition").toString());
    rxBoucle = QRegExp(param.value("rxStrBoucle").toString());
    rxBoucle2 =  QRegExp(param.value("rxStrBoucle2").toString());

    rxValAlea = QRegExp(param.value("rxValAlea").toString());
    rxValEnt = QRegExp(param.value("rxValEnt").toString());
    param.endGroup();

    QsciLexerAlgo *lexer= new QsciLexerAlgo();

    qDebug() << "Configuration de l'editeur...";
    // C'est mieux avec une police de charactère...
    lexer->setFont(QFont("Monospace",10));
    zoneTexte->setLexer(lexer);

    //Definition de l'API

    QsciAPIs *api = new QsciAPIs(lexer);
    api->load(":/textes/apiLang");
    api->prepare();

    //application et paramêtrage de l'API
    zoneTexte->setAutoCompletionSource(QsciScintilla::AcsAPIs);
    zoneTexte->setAutoCompletionThreshold(3); //Nombre de lettres pour commencer auto-completion
    zoneTexte->setIndentationGuides(true);
    zoneTexte->setIndentationsUseTabs(true); //Plus pratique
    zoneTexte->setAutoIndent(true);
    zoneTexte->setTabWidth(3); //Defaut 8

    zoneTexte->setMarginWidth(0,"0000");//On se débrouille pour que la marge soit assez grande (ici jusqu'au nombre 999)
    zoneTexte->setUtf8(true);

    qDebug()<< "\tPolice : " << zoneTexte->font()
            <<"\n\tNombre de lettres pour autocompletion : "<< zoneTexte->autoCompletionThreshold()
           <<"\n\tGuide d'indentation : " << zoneTexte->indentationGuides()
          <<"\n\tUtilisation des tabulation pour l'indentation : " << zoneTexte->indentationsUseTabs()
         <<"\n\tAuto indentation : " << zoneTexte->autoIndent()
        <<"\n\tLargeur des tabulations : "<< zoneTexte->tabWidth();
    qDebug()<< "Connection slots/signaux ...";



    connect(actionQuitter,SIGNAL(triggered()),this,SLOT(close()));
    connect(actionOptions,SIGNAL(triggered()),this,SLOT(affOptions()));
    connect(actionAnnuler,SIGNAL(triggered()),zoneTexte,SLOT(undo()));
    connect(actionRefaire,SIGNAL(triggered()),zoneTexte,SLOT(redo()));
    connect(actionToutEffacer,SIGNAL(triggered()),zoneTexte,SLOT(clear()));
    connect(actionTester,SIGNAL(triggered()),this,SLOT(tester()));
    connect(actionSauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarder()));
    connect(actionCharger,SIGNAL(triggered()),this,SLOT(ouvrir()));
    connect(actionNouveau,SIGNAL(triggered()),this,SLOT(nouveau()));

    nouveau();

}

void FenPrincipale::tester()
{

    qDebug()<<"Test lance...\n(Re)Initialisation des variables...";
    //On efface les affichages et l'historique
    affListeVar->clear();
    ActFinales.clear();
    NbVar.clear();
    NbVal.clear();
    TxVar.clear();
    TxVal.clear();
    LsVar.clear();
    LsVal.clear();
    Lignes.clear();


    //####################
    //Variables

    int pos=0;              // Position du curseur pour les recherches (remettre à 0 après chaque séries de recherches)
    int niveau_condition=0; // Le "niveau de condition" est le nombre de conditions dans lesquelles on est rentré (cf Conditions et Boucles)

    int pos_boucle = -1;    // Position de la fin d'une boucle
    int pos_origBoucle = -1;// Position du début d'une boucle
    dansBoucle2= false;

    qDebug()<<"Recuperation de l'algo...";
    QString contenu = zoneTexte->text(); //On récupère l'algorithme

    //########################
    //Préparation de l'analyse


    //On met tous les mots clés en majuscule
    QRegExp rx = QRegExp("si ");
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    contenu.replace(rx,QString("SI "));

    rx.setPattern("alors");
    contenu.replace(rx,QString("ALORS"));

    rx.setPattern("sinon");
    contenu.replace(rx,QString("SINON"));

    rx.setPattern("tant");
    contenu.replace(rx,QString("TANT"));

    rx.setPattern("que");
    contenu.replace(rx,QString("QUE"));

    rx.setPattern("faire");
    contenu.replace(rx,QString("FAIRE"));

    rx.setPattern("fin");
    contenu.replace(rx,QString("FIN"));

    rx.setPattern("saisir");
    contenu.replace(rx,QString("SAISIR"));

    rx.setPattern("afficher");
    contenu.replace(rx,QString("AFFICHER"));

    rx.setPattern("jusqu[ ']a ce");
    contenu.replace(rx,QString("JUSQU A CE"));

    rx.setPattern("repeter");
    contenu.replace(rx,QString("REPETER"));

    rx.setPattern("part_ent");
    contenu.replace(rx,QString("PART_ENT"));

    rx.setPattern("hasard");
    contenu.replace(rx,QString("HASARD"));

    rx.setPattern("debug");
    contenu.replace(rx,QString("DEBUG"));


    zoneTexte->setText(contenu); //On affiche l'Algorithme avec les mots en majuscules

    //On créé une variable nombre que l'utilisateur ne verra pas.
    //Cette valeur sera utilisée notament pour les conditions (pour avoir une valeur fixe...)
    contenu =  "VALUNIQUExNB = 0\n"+ zoneTexte->text();




    //On récupère chaque ligne pour un controle plus facile
    while( (pos = rxLigne.indexIn(contenu,pos)) != -1 )
    {
        Lignes << rxLigne.capturedTexts()[1];
        pos += rxLigne.matchedLength();
    }
    pos=0;



    // ########################################
    // Recherches des definitions des variables

    for (int i=0; i<Lignes.length();i++)
    {


        if(pos_origBoucle != -1 && pos_boucle != -1) //Si on est dans une boucle
        {
            if(i>=pos_boucle) //Si on a atteint la fin de la boucle
            {
                //On se replace au début de la boucle, à TANT QUE ... FAIRE
                //Ainsi, si on doit sauter la boucle, on la saute et on remet les variables à -1
                i=pos_origBoucle;


            }
        }


        //Pour chaque ligne, on regarde si elle correspond à une action, si elle correspond, on passe à la ligne suivante.

        //On place une condition (la fonction renvoie un bool) pour s'arreter si on trouve l'action.
        //C'est pour ça qu'il n'y a aucune action pour chaque condition.
        //L'exeption étant les structures conditionnelles et répetitives qui influent sur "i"

        //Si on rencontre un condition fausse
        //On va sauter toutes les actions jusqu'à un "sinon" ( condition vraie) ou la fin de la condition.
        if(execCondition(Lignes[i]) == 0)
        {

            pos=i+1; // On prend la position +1 ( on saute la ligne définissant la condition
            niveau_condition=1; //Le niveau correspond au nombre de condition dans lesquelles nous sommes rentrés
            //Celui-ci est à 1 Pour la condition primaire
            //Et atteint 0 quand on sort de cette condition.
            while (niveau_condition > 0 && pos < Lignes.count())
            {

                if(rxCondition.indexIn(Lignes[pos]) != -1)
                {
                    niveau_condition ++; //Si on entre dans une autre condition, on augment le niveau
                }
                else if (QRegExp("FIN").indexIn(Lignes[pos]) != -1)
                {
                    niveau_condition --;    //Si on sort d'une condition, on baisse le niveau
                    // Si on était dans la condition principale, on va en sortir
                }
                else if (QRegExp("SINON").indexIn(Lignes[pos]) != -1)
                {
                    if (niveau_condition == 1)
                    {
                        niveau_condition --;    //Si on était dans la principale, on veux executer la suite donc on sort

                    }
                }
                else if (rxBoucle.indexIn(Lignes[pos]) != -1)
                {
                    niveau_condition ++; //Si on rencontre une boucle, on monte le niveau
                }
                else if (pos == Lignes.length()-1)
                {
                    avertissement(this,"Attention, le mot-clé \"FIN\" n'a pas été rencontré en fin de condition fausse.\nLe fonctionnement de votre algorithme peut être compromis.\n\n***Nombre de \"FIN\" manquants : "+ intVersStr(niveau_condition) + " ***");
                }

                pos++; // On passe à la ligne suivante
            }

            i = pos-1; //Comme l'incrémentation se fait à la fin, il faut soustraire 1 pour avoir la bonne ligne
        }
        //Si on rencontre une condition vraie
        //On va supprimer ou rendre inactif tout le code qui ne sera pas executé
        else if(execCondition(Lignes[i]) == 1)
        {

            Lignes.removeAt(i); // On retire la ligne définissant la condition
            // Note : Lignes[i] devient Lignes[i+1]

            pos=i;
            niveau_condition = 1;

            while (niveau_condition > 0 && pos < Lignes.count())
            {

                if(rxCondition.indexIn(Lignes[pos]) != -1) //Si on rencontre une condition, on la conserve
                {                                          //elle sera traitée au prochain passage ...
                    niveau_condition ++;
                }
                else if (QRegExp("FIN").indexIn(Lignes[pos]) != -1)
                {
                    if(niveau_condition == 1)
                    {
                        Lignes.removeAt(pos);
                        //Si on est en sortie de condition, on retire le "FIN" ( plus propre ...)
                    }
                    niveau_condition --;
                }
                else if (QRegExp("SINON").indexIn(Lignes[pos]) != -1)
                {
                    if (niveau_condition == 1)      //Si on rencontre un "sinon" et qu'on est dans la principale
                        //( condition fausse )
                    {
                        Lignes[pos]="SI VALUNIQUExNB == 1 ALORS "; // On le remplace par une condition fausse que l'on traitera plus tard
                        // Or, VALUNIQUExNB == 0
                        niveau_condition = 0;      // On sort
                    }
                }
                if (pos == Lignes.length())
                {
                    avertissement(this,"Attention, le mot-clé \"FIN\" n'a pas été rencontré en fin de condition vraie.\nLe fonctionnement de votre algorithme peut être compromis.\n\n***Nombre de \"FIN\" manquants : "+ intVersStr(niveau_condition) + " ***");
                    niveau_condition-- ;
                }

                pos ++;
            }


            i--; //On prévoit la prochaine incrémentation ( au tour de boucle ) pour revenir au point de départ


        }
        //Si on entre pas dans la boucle, on traite de la meme façon qu'avec une condition fausse
        else if(execBoucle(Lignes[i]) == 0)
        {

            //Le traitement des boucles "REPETER" est inversé par rapport aux autres, ici on reboucle
            if(dansBoucle2)
            {
                if(pos_boucle == -1 )
                {
                    pos_boucle = i+1;
                }
            }
            // On remet à -1 les variables pour ne pas refaire une précédente boucle
            else
            {
                pos_boucle = -1;
                pos_origBoucle = -1;
                pos=i+1;            // On prend la position +1 ( on saute la ligne définissant la boucle

                niveau_condition = 1; //Le niveau correspond au nombre de condition dans lesquelles nous sommes rentrés
                //Celui-ci est à 1 Pour la condition primaire
                //Et atteint 0 quand on sort de cette condition.

                while (niveau_condition > 0 && pos < Lignes.count())
                {

                    if(rxCondition.indexIn(Lignes[pos]) != -1)
                    {
                        niveau_condition ++; //Si on entre dans une autre condition, on augment le niveau
                    }
                    if(rxBoucle.indexIn(Lignes[pos]) != -1)
                    {
                        niveau_condition ++; //Si on entre dans une autre boucle, on augment le niveau
                    }
                    else if (QRegExp("FIN").indexIn(Lignes[pos]) != -1)
                    {
                        niveau_condition --;    //Si on sort d'une condition, on baisse le niveau
                        // Si on était dans la condition principale, on en sort
                    }
                    else if (pos == Lignes.length())
                    {
                        avertissement(this,"Attention, le mot-clé \"FIN\" n'a pas été rencontré en fin de boucle.\nLe fonctionnement de votre algorithme peut être compromis.\n\n***Nombre de \"FIN\" manquants : "+ intVersStr(niveau_condition) + " ***");
                    }
                    pos++; // On passe à la ligne suivante
                }


                i = pos-1; //Comme l'incrémentation se fait à la fin, il faut soustraire 1 pour avoir la bonne ligne
            }
        }

        else if(execBoucle(Lignes[i]) == 1) // Si on entre dans une boucle à executer,
        {
            //Le traitement des boucles "REPETER" est inversé par rapport aux autres, ici on sort
            if(dansBoucle2)
            {
                dansBoucle2 = false;
                pos_boucle = -1;
                pos_origBoucle = -1;


            }
            else if(pos_origBoucle == -1)
            {



                pos_origBoucle=i; // Si on était pas dans une boucle, on prend la valeur de départ
                // ATTENTION : Ne permet qu'une boucle à la fois
                niveau_condition = 1;
                //Le niveau correspond au nombre de condition dans lesquelles nous sommes rentrés
                //Celui-ci est à 1 Pour la condition primaire
                //Et atteint 0 qu}and on sort de cette condition.



                pos=i; // On prend la position


                // On va parcourir l'algorithme jusqu'à trouver la fin de la boucle

                while (niveau_condition > 0 && pos < Lignes.count())
                {
                    if(rxCondition.indexIn(Lignes[pos]) != -1)
                    {
                        niveau_condition ++; //Si on entre dans une autre condition, on augment le niveau
                    }
                    if(pos != pos_origBoucle && rxBoucle.indexIn(Lignes[pos]) != -1)
                    {
                        niveau_condition ++; //Si on entre dans une autre boucle, on augmente le niveau
                    }
                    else if (QRegExp("FIN").indexIn(Lignes[pos]) != -1)
                    {// On prend la position
                        niveau_condition --;    //Si on sort d'une condition, on baisse le niveau
                        // Si on était dans la condition principale, on en sort
                    }
                    else if (pos == Lignes.length()-1)
                    {
                        avertissement(this,"Attention, le mot-clé \"FIN\" n'a pas été rencontré en fin de boucle.\nLe fonctionnement de votre algorithme peut être compromis.\nLa boucle en cours a été stoppée.\n\n***Nombre de \"FIN\" manquants : "+ intVersStr(niveau_condition) + " ***");
                        niveau_condition = 0;
                        pos_boucle = -1;
                        pos_origBoucle = -1;
                    }

                    pos++; // On passe à la ligne suivante

                }


                pos--;
                pos_boucle=pos;
            }
            //Comme l'incrémentation se fait à la fin, il faut soustraire 1 pour avoir la bonne ligne
        }

        else if(defVarTx(Lignes[i])) {}//Variables de type chaîne
        else if(defVarLs(Lignes[i])){}  //Variables de type liste
        else if(defVarNb(Lignes[i])){}   //Variables numériques
        else if(modVarOpSurSoisMeme(Lignes[i])){} //Opération sur soi-meme
        else if(modListe(Lignes[i],true)){}  //Modifications d'une valeur d'une liste
        else if(modSaisie(Lignes[i])){}      //Saisie d'une valeur
        else if(affVal(Lignes[i])){} //Affichage d'une valeur
        else if(QRegExp("REPETER").indexIn(Lignes[i]) != -1 )
        {
            if( ! dansBoucle2)
            {
                dansBoucle2 = true;
                pos_origBoucle = i;
            }

        }
        else if(QRegExp("DEBUG").indexIn(Lignes[i]) != -1)
        {
            QString msg;

            msg += "--Variables--\n";
            msg += "posOrig : "+ intVersStr(pos_origBoucle)+ "\n";
            msg += "posFin : "+ intVersStr(pos_boucle)+ "\n";
            msg += "dansBoucle2 : "+ intVersStr(dansBoucle2)+ "\n";
            msg += "niveauCondition : " + intVersStr(niveau_condition) + "\n";


            info(this,"Informations de Debug", msg);


        }
    }








    for (int i = 1 ; i < NbVar.size() ; i++)
    {
        affListeVar->addItem(QString("NOMBRE " + NbVar.at(i) + " = " + NbVal.at(i).toString()));
    }
    for (int i = 0 ; i < TxVar.size() ; i++)
    {
        affListeVar->addItem(QString("CHAINE " + TxVar.at(i) + " = \"" + TxVal.at(i) + "\""));
    }
    for (int i = 0 ; i < LsVar.size() ; i++)
    {
        QString valListe;
        for (int j = 0 ; j < LsVal.at(i).size() ; j++)
        {

            valListe += LsVal.at(i).at(j).toString();
            if(j != LsVal.at(i).size()-1)
            {
                valListe +=  " | ";
            }

        }

        affListeVar->addItem(QString("LISTE " + LsVar.at(i) + " =  [" + valListe + "]"));
    }
    //Pratique pour les tests
    //        for (int i = 0 ; i < Lignes.size() ; i++)
    //        {
    //            affListeVar->addItem(QString(Lignes.at(i) ));
    //        }


}

//Renvoie une chaine du type "une chaine" sans les guillemets
//Ex : retirerGuillemets("\"plop\"") == plop
QString FenPrincipale::retirerGuillemets(QString ch)
{
    QRegExp sansGuillemets = QRegExp("\"([^\"]*)\"");

    if(QRegExp("\"[^\"]*\"").exactMatch(ch))
    {
        sansGuillemets.indexIn(ch);
        return sansGuillemets.capturedTexts()[1];
    }
    else
    {
        return ch;
    }
}

//Execute une opération arithmétique et renvoie le résultat (numérique) sous la forme d'un QString
QString FenPrincipale::execOp(QString Op)
{



    int i = 0;
    int pos = 0;
    QString chActu=Op;
    QRegExp var = QRegExp("([a-zA-Z]{1}[a-zA-Z0-9_]*)");
    QRegExp valListe = QRegExp(def_rxValListe);
    QRegExp parentheses = QRegExp("\\(([0-9()*\\-/+% .,]+)\\)");
    QRegExp multiVarImplicite = QRegExp("("+def_rxNombre+")"+"("+def_rxVariable+")");
    QRegExp multiParenthesesImplicite = QRegExp("("+def_rxNombre+")\\(");
    parentheses.setMinimal(1);
    QRegExp opPrio = QRegExp("(-?\\d+(?:\\.|,)?\\d*) ?(\\*|/|%) ?(-?\\d+(?:\\.|,)?\\d*)");
    QRegExp opNormales = QRegExp("(-?\\d+(?:\\.|,)?\\d*) ?(\\+|-) ?(-?\\d+(?:\\.|,)?\\d*)");
    QStringList chSuccessives;
    QString res;

    //Traitement des nombres aléatoires
    while( (pos = rxValAlea.indexIn(chActu,pos)) != -1 )
    {
        QString borneMin = rxValAlea.capturedTexts()[2];
        QString borneMax = rxValAlea.capturedTexts()[1];

        double rdmax = RAND_MAX; //RandMax défini dans <stdlib.h> et <cstdlib>
        double nb = (qrand()+1)/(rdmax+1);

        if (borneMax != "" && borneMin != "" )
        {

            nb= nb*execOp(QString(borneMin+"-"+borneMax)).toDouble();
            nb += execOp(borneMax).toDouble();
            nb = QVariant(nb).toInt();

            //nb = partie entiere de nb*(max-min)+min

        }
        else if (borneMax != "")
        {

            nb= nb*execOp(borneMax).toDouble();
            nb = QVariant(nb).toInt();
        }
        chActu.replace(rxValAlea,QVariant(nb).toString());
    }
    pos=0;
    //Traitement des parties entieres
    while( (pos = rxValEnt.indexIn(chActu,pos)) != -1 )
    {

        QString val = rxValEnt.capturedTexts()[1];
        QString nb = execOp(val).left(execOp(val).indexOf("\."));

        qDebug()<< "\tPartie entiere de " << val << "(" << execOp(val) << ") : " << nb << "(" <<execOp(val).indexOf("\.")<< ")";
        chActu.replace(rxValEnt,QVariant(nb).toString());
    }
    pos=0;

    if (chActu == "")
    { return QString("0");}
    while ((pos = valListe.indexIn(chActu, pos)) != -1)
    {
        chActu.replace(valListe.capturedTexts()[0],recupValListe(valListe.capturedTexts()[0]).toString());
        pos+=valListe.matchedLength();
    }
    pos = 0;
    while ((pos = multiVarImplicite.indexIn(chActu, pos)) != -1)
    {
        chActu.replace(multiVarImplicite.capturedTexts()[0],QString(multiVarImplicite.capturedTexts()[1] +"*" + multiVarImplicite.capturedTexts()[2]));
        pos+=multiVarImplicite.matchedLength();
    }
    pos = 0;
    while ((pos = multiParenthesesImplicite.indexIn(chActu, pos)) != -1)
    {
        chActu.replace(multiParenthesesImplicite.capturedTexts()[0],QString(multiParenthesesImplicite.capturedTexts()[1] +"*("));
        pos+=multiParenthesesImplicite.matchedLength();
    }
    pos = 0;
    while ((pos = var.indexIn(chActu, pos)) != -1) //Tant qu'on trouve quelque chose...
    {

        if(NbVar.contains(var.capturedTexts()[1]))
        {

            chActu.replace(var.capturedTexts()[1],NbVal[NbVar.indexOf(var.capturedTexts()[1])].toString());
        }
        else
        {
            chActu.replace(var.capturedTexts()[1],0);
        }
        pos += var.matchedLength();

    }

    chSuccessives << chActu;
    do
    {
        chActu = chSuccessives[0];
        i=0;
        while (parentheses.indexIn(chActu) != -1 )
        {

            chActu = parentheses.capturedTexts()[1];
            chSuccessives << chActu;
            i++;

        }
        for(i;i>=0;i--)
        {

            chActu = chSuccessives[i];

            while ((opPrio.indexIn(chActu)) != -1) //Tant qu'on trouve quelque chose...
            {
                double nb1 = QVariant(opPrio.capturedTexts()[1]).toDouble();
                double nb2 = QVariant(opPrio.capturedTexts()[3]).toDouble();
                QString signe = opPrio.capturedTexts()[2];

                if(signe == "*" )
                {
                    res = QVariant(nb1*nb2).toString();
                }
                else if(signe == "/")
                {
                    res = QVariant(nb1/nb2).toString();
                }
                else
                {

                    int inb1 = QVariant(nb1).toInt();
                    int inb2 = QVariant(nb2).toInt();
                    res = QVariant(inb1 % inb2).toString();
                }

                chActu.replace(opPrio.capturedTexts()[0],res);
            }

            while ((opNormales.indexIn(chActu)) != -1) //Tant qu'on trouve quelque chose...
            {
                double nb1 = QVariant(opNormales.capturedTexts()[1]).toDouble();
                double nb2 = QVariant(opNormales.capturedTexts()[3]).toDouble();
                QString signe = opNormales.capturedTexts()[2];
                QString res;
                if(signe == "+" )
                {
                    res = QVariant(nb1+nb2).toString();

                }
                else
                {
                    res = QVariant(nb1-nb2).toString();
                }


                chActu.replace(opNormales.capturedTexts()[0],res);
            }

            if(i > 0)
            {
                for(int j=i; j > 0; j--)
                {

                    chSuccessives[j-1].replace(QString("("+chSuccessives[i]+")"),chActu);
                    chSuccessives.removeLast();

                }
            }
            else
            {
                chSuccessives[i] = chActu;

            }

        }
    } while (parentheses.indexIn(chSuccessives[0]) != -1 );
    return chSuccessives[0];

}

//Renvoie la valeur d'une case d'une liste
QVariant FenPrincipale::recupValListe(QString ch)
{
    QRegExp rx = QRegExp(def_rxValListe);
    if(rx.indexIn(ch) != -1 && LsVar.contains(rx.capturedTexts()[1]))
    {
        return LsVal[LsVar.indexOf(rx.capturedTexts()[1])][QVariant(execOp(rx.capturedTexts()[2])).toInt()];
    }
    else
    {
        return QVariant();
    }
}


bool FenPrincipale::defVarNb(QString ligne)
{
    QString nvVal;

    if ( rxNbVar.indexIn(ligne) != -1) //S'il y a qqch
    {
        if(NbVar.contains(rxNbVar.capturedTexts().at(1))) // Si la variable existe déjà...
        {

            if (rxNbVar.capturedTexts()[2] == "") //Si on a écrit '<var> est un nombre'
            {

                NbVal.replace(NbVar.indexOf(QString(rxNbVar.capturedTexts().at(1))),QVariant(0)) ; //Valeur = 0
                ActFinales << "[M](L)" + NbVar.value(NbVar.indexOf(QString(rxNbVar.capturedTexts().at(1)))) + "="+ NbVal.value(NbVar.indexOf(QString(rxNbVar.capturedTexts().at(1)))).toString();

            }
            else //Si on a écrit '<var> = <nombre>'
            {
                if(rxNbVar.capturedTexts()[3] != "")
                {
                    nvVal = execOp(QVariant(LsVal[LsVar.indexOf(rxNbVar.capturedTexts()[3])][QVariant(execOp(rxNbVar.capturedTexts()[4])).toInt()]).toString());
                }
                else
                {
                    nvVal = execOp(rxNbVar.capturedTexts().at(2));
                }
                NbVal.replace(NbVar.indexOf(QString(rxNbVar.capturedTexts().at(1))),nvVal); // Valeur = <nombre>
                ActFinales << "[M](L)"+NbVar.value(NbVar.indexOf(QString(rxNbVar.capturedTexts().at(1)))) + "="+ nvVal;
            }
        }
        else // Si on créé la variable
        {
            NbVar << rxNbVar.capturedTexts().at(1); // On ajoute le nom de la variable au tableau correspondant
            if (rxNbVar.capturedTexts().at(2) == "") //Si on a écrit '<var> est un nombre'
            {
                NbVal << QVariant(0) ; // On ajoute la valeur au tableau correspondant, valeur par défaut : 0
                ActFinales << "[I](L)"+NbVar.last() + "="+ NbVal.last().toString();
            }
            else //Si on a écrit '<var> = <nombre>'
            {
                nvVal = execOp(rxNbVar.capturedTexts().at(2));
                NbVal << nvVal.toDouble(); // On ajoute la valeur <nombre> de la variable au tableau correspondant
                ActFinales << "[I](N)"+NbVar.last() + "="+ NbVal.last().toString();
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}
bool FenPrincipale::defVarTx(QString ligne)
{
    QString nvVal;
    QRegExp concatenation = QRegExp("(?:(\"[^\"]*\")|([a-zA-Z]{1}[a-zA-Z0-9_]*))(?: ?\\+ ?(?:(\"[^\"]*\")|([a-zA-Z]{1}[a-zA-Z0-9_]*)))?");

    int pos = 0;
    //! ####A SUPPRIMER###
    int z;
    z = 0;
    //! ##################
    if (rxTxVar.indexIn(ligne) != -1) //Tant qu'on trouve quelque chose...
    {
        QString ch_tot = rxTxVar.capturedTexts()[0];
        QString ch = rxTxVar.capturedTexts()[2];
        QString ch_prec;
        while(concatenation.indexIn(ch) != -1 && ch != ch_prec)
        {
            z++;
            ch_prec = ch;
            QString ch1 = concatenation.capturedTexts()[1];
            QString var1 = concatenation.capturedTexts()[2];
            QString ch2 = concatenation.capturedTexts()[3];
            QString var2 = concatenation.capturedTexts()[4];
            qDebug() << "Déclaration d'une chaine"
                     <<"\n\tLigne : " << ch_tot
                    <<"\n\tChaine de travail : " << ch
                   <<"\n\tPassage No "<< z
                  <<"\n\tVariable : " << rxTxVar.capturedTexts()[1]
                 << "\n\tChaine : " <<  concatenation.capturedTexts()[0]
                 << "\n\tSous chaine 1 : " <<retirerGuillemets(ch1)
                 << "\n\tVariable 1 : " << var1
                 << "\n\tSous chaine 2 : " << retirerGuillemets(ch2)
                 << "\n\tVariable 2 : " << var2;

            if(! ch1.isEmpty())
            {
                qDebug() << "\t-->Application Chaine 1";
                nvVal = retirerGuillemets(ch1);
            }
            else if(! var1.isEmpty())
            {
                qDebug() << "\t-->Application Variable 1";
                if(TxVar.contains(var1))
                    nvVal = TxVal[TxVar.indexOf(var1)];
                else if (NbVar.contains(var1))
                    nvVal = NbVal[NbVar.indexOf(var1)].toString();
            }
            if(! ch2.isEmpty())
            {
                qDebug() << "\t-->Application Chaine 2";
                nvVal += retirerGuillemets(ch2) ;
            }
            else if(! var2.isEmpty())
            {
                qDebug() << "\t-->Application Variable 2";
                if(TxVar.contains(var2))
                    nvVal += TxVal[TxVar.indexOf(var2)] ;
                else if (NbVar.contains(var2))
                    nvVal += NbVal[NbVar.indexOf(var2)].toString() ;
            }

            ch_tot.replace(concatenation.capturedTexts()[0],QString("\"" +nvVal+"\""));

            if(rxTxVar.indexIn(ch_tot) != -1)
            {

               ch_tot = rxTxVar.capturedTexts()[0];
                ch = rxTxVar.capturedTexts()[2];

            }
            qDebug() << "\tResultat, ligne : " << ch_tot;
        }

        if(TxVar.contains(rxTxVar.capturedTexts()[1]))
        {

            /*  if (rxTxVar.capturedTexts()[2] == "")
            {
                TxVal.replace(TxVar.indexOf(QString(rxTxVar.capturedTexts()[1])),"") ;
                ActFinales << "[M](C)"+TxVar.value(TxVar.indexOf(QString(rxTxVar.capturedTexts().at(1)))) + "="+ TxVal.value(TxVar.indexOf(QString(rxTxVar.capturedTexts().at(1))));

            }
            else
            {*/
            TxVal[TxVar.indexOf(QString(rxTxVar.capturedTexts()[1]))] = nvVal;
            ActFinales << "[M](C)"+TxVar.value(TxVar.indexOf(QString(rxTxVar.capturedTexts().at(1)))) + "="+ TxVal.value(TxVar.indexOf(QString(rxTxVar.capturedTexts().at(1))));
            //}
        }
        else
        {
            TxVar << rxTxVar.capturedTexts()[1]; // On ajoute le nom de la variable au tableau correspondant
            /*if (rxTxVar.capturedTexts().at(2) == "")
            {
                TxVal << QString("") ;
                ActFinales << "[I](C)"+TxVar.last() + "="+ TxVal.last();
            }
            else
            {*/
            TxVal << nvVal; // On ajoute la valeur de la variable au tableau correspondant
            ActFinales << "[I](C)"+TxVar.last() + "="+ TxVal.last();
            // }
        }
        return true;
    }
    else
    {
        return false;
    }
}
bool FenPrincipale::defVarLs(QString ligne)
{
    if (rxLsVar.indexIn(ligne) != -1 && ! LsVar.contains(rxLsVar.capturedTexts()[1])) //Si on trouve qqch et qu'on a pas déclaré la liste
    {

        LsVar << rxLsVar.capturedTexts().at(1); // On ajoute le nom de la variable au tableau correspondant
        LsVal <<  QList<QVariant>(); // La liste est initialisée à vide
        ActFinales << "[I](L)"+LsVar.last();

        return true;

    }
    else
    {
        return false;
    }
}

bool FenPrincipale::modVarOpSurSoisMeme(QString ligne)
{
    if (rxVarOpSurSoisMeme.indexIn(ligne) != -1) //Tant qu'on trouve quelque chose...
    {
        int i;

        QString signe = rxVarOpSurSoisMeme.capturedTexts()[2];
        QString var = rxVarOpSurSoisMeme.capturedTexts()[1];
        QString val = rxVarOpSurSoisMeme.capturedTexts()[3];

        while(val[0] == ' ')
        {
            val.remove(0,1);
        }

        qDebug() <<"\tOperation : "<< var << signe << val;

        if(signe == "<<")
        {

            if(LsVar.contains(var))
            {

                if(QRegExp("\"([^\"]*)\"|-?\\d+(?:\\.|,)?\\d*").exactMatch(val))
                {
                    LsVal[LsVar.indexOf(var)] << retirerGuillemets(val);
                }
                else if (QRegExp("[a-zA-Z]{1}[a-zA-Z0-9_]*").exactMatch(val))
                {

                    if(NbVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << NbVal[NbVar.indexOf(val)];

                    }
                    else if(TxVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << TxVal[TxVar.indexOf(val)];
                    }
                    else if(LsVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << LsVal[LsVar.indexOf(val)];
                    }

                }
            }
            if(TxVar.contains(var))
            {
                if(QRegExp("\"([^\"]*)\"|-?\\d+(?:\\.|,)?\\d*").exactMatch(val))
                {
                    TxVal[TxVar.indexOf(var)] += retirerGuillemets(val);
                }
                else if (QRegExp("[a-zA-Z]{1}[a-zA-Z0-9_]*").exactMatch(val))
                {
                    if(NbVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << NbVal[NbVar.indexOf(val)];
                    }
                    else if(TxVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << TxVal[TxVar.indexOf(val)];
                    }
                    else if(LsVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << LsVal[LsVar.indexOf(val)];
                    }

                }
            }

        }
        else if (signe == "+=")
        {
            if(LsVar.contains(var))
            {
                if(QRegExp("\"([^\"]*)\"|-?\\d+(?:\\.|,)?\\d*").exactMatch(val))
                {
                    LsVal[LsVar.indexOf(var)] << retirerGuillemets(val);
                }
                else if (QRegExp("[a-zA-Z]{1}[a-zA-Z0-9_]*").exactMatch(val))
                {
                    if(NbVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << NbVal[NbVar.indexOf(val)];
                    }
                    else if(TxVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << TxVal[TxVar.indexOf(val)];
                    }
                    else if(LsVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << LsVal[LsVar.indexOf(val)];
                    }

                }
            }
            else if(TxVar.contains(var))
            {
                if(QRegExp("\"([^\"]*)\"|-?\\d+(?:\\.|,)?\\d*").exactMatch(val))
                {
                    TxVal[TxVar.indexOf(var)] += retirerGuillemets(val);
                }
                else if (QRegExp("[a-zA-Z]{1}[a-zA-Z0-9_]*").exactMatch(val))
                {
                    if(NbVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << NbVal[NbVar.indexOf(val)];
                    }
                    else if(TxVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << TxVal[TxVar.indexOf(val)];
                    }
                    else if(LsVar.contains(val))
                    {
                        LsVal[LsVar.indexOf(var)] << LsVal[LsVar.indexOf(val)];
                    }

                }
            }
            else if(NbVar.contains(var))
            {
                NbVal[NbVar.indexOf(var)] = NbVal[NbVar.indexOf(var)].toDouble() + execOp(val).toDouble();
            }
        }
        else if (signe == "-=")
        {
            if(LsVar.contains(var))
            {
                if(QRegExp("\"([^\"]*)\"|-?\\d+(?:\\.|,)?\\d*").exactMatch(val))
                {

                    int x = LsVal[LsVar.indexOf(var)].size();
                    for (i = 0 ; i < x ; i++)
                    {

                        if(LsVal[i].contains(retirerGuillemets(val)) and LsVal[i].size()!=0)
                        {

                            LsVal[LsVar.indexOf(var)].removeAt(i) ;
                            x--;
                            i--;
                        }
                    }

                }
                else if (QRegExp("[a-zA-Z]{1}[a-zA-Z0-9_]*").exactMatch(val))
                {
                    bool liste = false;
                    if(NbVar.contains(val))
                    {
                        val = NbVal[NbVar.indexOf(val)].toString();
                    }
                    else if(TxVar.contains(val))
                    {
                        val = TxVal[TxVar.indexOf(val)];
                    }
                    else if(LsVar.contains(val))
                    {
                        //val = LsVal[LsVar.indexOf(val)];
                        liste = true;
                    }
                    if(!liste)
                    {
                        for (i = 0 ; i < LsVar[LsVar.indexOf(var)].size()  ; i++)
                        {
                            if(LsVal[LsVar.indexOf(var)][i]== val)
                            {
                                LsVal[LsVar.indexOf(var)].removeAt(LsVal[i].indexOf(val));
                            }
                        }

                    }
                    else if (liste)
                    {
                        int x = LsVal[LsVar.indexOf(var)].size();
                        for (i = 0 ; i < x ; i++)
                        {

                            if(LsVal[LsVar.indexOf(var)].contains(LsVal[LsVar.indexOf(var)][i]) and LsVal[LsVar.indexOf(var)].size() != 0)
                            {
                                LsVal[LsVar.indexOf(var)].removeAt(i) ;
                                x--;
                                i--;
                            }
                        }
                    }


                }
            }
            else if(TxVar.contains(var))
            {
                TxVal[TxVar.indexOf(var)].remove(retirerGuillemets(val));
            }
            else if(NbVar.contains(var))
            {
                if(QRegExp("-?\\d+(?:\\.|,)?\\d*").exactMatch(val))
                {
                    NbVal[NbVar.indexOf(var)] = NbVal[NbVar.indexOf(var)].toDouble() - val.toDouble();
                }
                else if (QRegExp("[a-zA-Z]{1}[a-zA-Z0-9_]*").exactMatch(val))
                {
                    if(NbVar.contains(val))
                    {
                        NbVal[NbVar.indexOf(var)] =NbVal[NbVar.indexOf(var)].toDouble() - NbVal[NbVar.indexOf(val)].toDouble();
                    }
                }
            }

        }
        else if (signe == "/=")
        {
            if(NbVar.contains(var))
            {
                NbVal[NbVar.indexOf(var)] = NbVal[NbVar.indexOf(var)].toDouble() / val.toDouble();
            }
        }
        else if (signe == "*=")
        {
            if(NbVar.contains(var))
            {
                NbVal[NbVar.indexOf(var)] = NbVal[NbVar.indexOf(var)].toDouble() * val.toDouble();
            }
        }
        else if (signe == "%=")
        {
            if(NbVar.contains(var))
            {
                NbVal[NbVar.indexOf(var)] = NbVal[NbVar.indexOf(var)].toInt() %  val.toInt();
            }
        }
        else if (signe == "++")
        {
            if(NbVar.contains(var))
            {
                NbVal[NbVar.indexOf(var)] =  NbVal[NbVar.indexOf(var)].toDouble() +1;
            }
        }
        else if (signe == "--")
        {
            if(NbVar.contains(var))
            {
                NbVal[NbVar.indexOf(var)] = NbVal[NbVar.indexOf(var)].toDouble() -1;
            }
        }
        else
        {
            return false;
        }


        return true;
    }
    else
    {
        return false;
    }

}
bool FenPrincipale::modSaisie (QString ligne)
{
    QInputDialog dialog;
    dialog.setModal(true);
    bool ok;
    if ( rxRecupSaisie.indexIn(ligne) != -1)
    {
        QString var = rxRecupSaisie.capturedTexts()[1];
        QString indice = rxRecupSaisie.capturedTexts()[2];

        if (indice != "")
        {
            QString valeur = dialog.getText(this, "Saisie d'une valeur",
                                            QString("Veuillez saisir la valeur de l'indice "+ QVariant(execOp(indice)).toString() + " de la liste "+ var+".<br/>Pour placer une chaîne, entourez votre saisie de guillemets."),
                                            QLineEdit::Normal,
                                            QString(),
                                            &ok);
            if(ok)
            {
                if( ! valeur.contains("\""))
                {
                    modListe(var,QVariant(execOp(indice)).toInt(),execOp(valeur));
                }
                else
                {
                    modListe(var,QVariant(execOp(indice)).toInt(),retirerGuillemets(valeur));
                }

            }
            else
            {
                return true;
            }
        }
        else
        {
            if(NbVar.contains(var))
            {
                QString valeur = dialog.getText(this, "Saisie d'une valeur",
                                                "Veuillez saisir une valeur pour la variable numérique "+ var + " .<br/>Vous pouvez saisir un nombre ou une expression prenant en compte des variables déjà existantes.",
                                                QLineEdit::Normal,
                                                QString(),
                                                &ok);
                if(ok)
                {
                    NbVal[NbVar.indexOf(var)] = execOp(valeur);
                    return true;
                }
                else
                {
                    return true;
                }
            }
            else if(TxVar.contains(var))
            {
                QString valeur = dialog.getText(this, "Saisie d'une valeur",
                                                "Veuillez saisir une valeur pour la variable texte (chaîne) "+ var + " .<br/>Vous pouvez placer n'importe quel caractère sauf des guillemets (\").",
                                                QLineEdit::Normal,
                                                QString(),
                                                &ok);
                if(ok)
                {
                    TxVal[TxVar.indexOf(var)] = valeur;
                    return true;
                }
                else
                {
                    return true;
                }
            }
            else if(LsVar.contains(var))
            {
                QString valeur = dialog.getText(this, "Saisie d'une valeur",
                                                "Veuillez saisir une valeur à ajouter à la fin de la liste "+ var + " .<br/>Pour placer une chaîne, entourez votre saisie de guillemets.",
                                                QLineEdit::Normal,
                                                QString(),
                                                &ok);
                if(ok)
                {
                    if( ! valeur.contains("\""))
                    {
                        LsVal[LsVar.indexOf(var)] << execOp(valeur);
                    }
                    else
                    {
                        LsVal[LsVar.indexOf(var)] << retirerGuillemets(valeur);
                    }
                    return true;
                }
                else
                {
                    return true;
                }
            }
            else
            {
                return false;
            }

        }
    }
    else
    {
        return false;
    }
}

bool FenPrincipale::modListe(QString ligne, bool creer_si_innexistant)
{
    if (rxModifListe.indexIn(ligne) != -1)
    {
        QString liste = rxModifListe.capturedTexts()[1];
        int indice = QVariant(execOp(rxModifListe.capturedTexts()[2])).toInt();
        QString valeur = rxModifListe.capturedTexts()[3];
        if ( ! valeur.contains("\""))
        {
            valeur = execOp(valeur);
        }
        if(LsVar.contains(liste) && indice >= 0)
        {
            int i= LsVal[LsVar.indexOf(liste)].count();
            for(i ; i<=indice ;i++)
            {
                LsVal[LsVar.indexOf(liste)] << QVariant("");
            }
            LsVal[LsVar.indexOf(liste)][indice]=valeur;
            return true;
        }
        else if (creer_si_innexistant)
        {
            defVarLs(QString(liste+"[]"));
            return modListe(ligne,false);
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
bool FenPrincipale::modListe(QString liste, int indice, QVariant valeur, bool creer_si_innexistant)
{

    indice--;
    if(LsVar.contains(liste) && indice >= 0)
    {
        int i= LsVal[LsVar.indexOf(liste)].count();
        for(i ; i<=indice ;i++)
        {
            LsVal[LsVar.indexOf(liste)] << QVariant("");
        }

        LsVal[LsVar.indexOf(liste)][indice]=valeur;
        return true;
    }
    else if (creer_si_innexistant)
    {
        defVarLs(QString(liste+"[]"));
        return modListe(liste,indice,valeur,false);
    }

    return false;
}

bool FenPrincipale::affVal(QString ligne)
{
    if(rxAfficheVar.indexIn(ligne) != -1)
    {

        QString val;
        QString var = rxAfficheVar.capturedTexts()[1];


        if(NbVar.contains(var))
        {

            val = NbVal[NbVar.indexOf(var)].toString();
            info(this,"Affichage d'une valeur",QString ("La variable numérique " + var + " a pour valeur " + val));
        }
        else if(TxVar.contains(var))
        {
            val = TxVal[TxVar.indexOf(var)];
            info(this,"Affichage d'une valeur",QString ("La variable texte (chaîne)" + var + " a pour valeur " + val));
        }
        else if(LsVar.contains(var))
        {

            int i = LsVar.indexOf(var);
            int j = execOp(rxAfficheVar.capturedTexts()[2]).toInt();
            if(rxAfficheVar.capturedTexts()[2] != "")
            {
                val = LsVal[i][j].toString();
                info(this,"Affichage d'une valeur",QString ("La liste" + var + "à l'indice "+ j +" a pour valeur " + val));
            }
            else
            {
                for (int j = 0 ; j < LsVal[i].size() ; j++)
                {

                    val += LsVal[i][j].toString();
                    if(j != LsVal[i].size()-1)
                    {
                        val +=  " | ";
                    }

                }
                info(this,"Affichage d'une valeur",QString ("La liste" + var + " contient les valeurs \n{" + val+"}"));
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

int FenPrincipale::execCondition(QString ligne)
{
    /*
               ################################
               Si retour = -1, pas de condition
               Si retour = 0, condition fausse
               Si retour = 1, condition vraie
               ################################
            */
    int res = -1;
    if (rxCondition.indexIn(ligne) != -1)
    {
        QString var = rxCondition.capturedTexts()[1];
        QString listeVar = rxCondition.capturedTexts()[2];
        QString indiceVar = rxCondition.capturedTexts()[3];
        QString signe = rxCondition.capturedTexts()[4];
        QString comp = rxCondition.capturedTexts()[5];
        QString listeComp = rxCondition.capturedTexts()[6];
        QString indiceListeComp = rxCondition.capturedTexts()[7];

        res=0;
        if (signe == "==")
        {

            if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
            {
                if(NbVar.contains(var))
                {

                    if(NbVal[NbVar.indexOf(var)].toDouble() == QVariant(execOp(comp)).toDouble())
                    {
                        res= 1;
                    }
                    else
                    {
                        res= 0;
                    }
                }
                else if(QRegExp(def_rxValListe).exactMatch(var))
                {
                    if(recupValListe(var) == QVariant(execOp(comp)))
                    { res= 1;}
                    else
                    { res= 0;}
                }
                else if(TxVar.contains(var))
                {
                    if(TxVal[TxVar.indexOf(var)] == QVariant(execOp(comp)))
                    { res= 1;}
                    else
                    {res= 0;}
                }
            }

        }
        else if (signe == "!=")
        {
            if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
            {
                if(NbVar.contains(var))
                {
                    if(NbVal[NbVar.indexOf(var)] != QVariant(execOp(comp)))
                        return 1;
                    else
                        return 0;
                }
                else if(QRegExp(def_rxValListe).exactMatch(var))
                {
                    if(recupValListe(var) != QVariant(execOp(comp)))
                        return 1;
                    else
                        return 0;
                }
                else if(TxVar.contains(var))
                {
                    if(TxVal[TxVar.indexOf(var)] != QVariant(execOp(comp)))
                        return 1;
                    else
                        return 0;
                }

            }

        }
        else if (signe == "<=")
        {
            if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
            {
                if(NbVar.contains(var))
                {
                    if(NbVal[NbVar.indexOf(var)].toDouble() <= QVariant(execOp(comp)).toDouble())
                        return 1;
                    else
                        return 0;
                }
            }
        }
        else if (signe == ">=")
        {
            if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
            {
                if(NbVar.contains(var))
                {
                    if(NbVal[NbVar.indexOf(var)].toDouble() >= QVariant(execOp(comp)).toDouble())
                        return 1;
                    else
                        return 0;
                }
            }
        }
        else if (signe == "<")
        {
            if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
            {
                if(NbVar.contains(var))
                {
                    if(NbVal[NbVar.indexOf(var)].toDouble() < QVariant(execOp(comp)).toDouble())
                        return 1;
                    else
                        return 0;
                }
            }
        }
        else if (signe == ">")
        {
            if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
            {
                if(NbVar.contains(var))
                {
                    if(NbVal[NbVar.indexOf(var)].toDouble() > QVariant(execOp(comp)).toDouble())
                        return 1;
                    else
                        return 0;
                }
            }
        }

    }
    return res;
}

int FenPrincipale::execBoucle(QString ligne)
{
    /*
               ################################
               Si retour = -1, pas de boucle
               Si retour = 0 , condition fausse
               Si retour = 1 , Boucle 1
               ################################
     */
    int res = -1;
    QString var;
    QString listeVar;
    QString indiceVar;
    QString signe;
    QString comp;
    QString listeComp;
    QString indiceListeComp;
    if (rxBoucle.indexIn(ligne) != -1 && ! dansBoucle2  )
    {

        var = rxBoucle.capturedTexts()[1];
        listeVar = rxBoucle.capturedTexts()[2];
        indiceVar = rxBoucle.capturedTexts()[3];
        signe = rxBoucle.capturedTexts()[4];
        comp = rxBoucle.capturedTexts()[5];
        listeComp = rxBoucle.capturedTexts()[6];
        indiceListeComp = rxBoucle.capturedTexts()[7];

    }
    else if (rxBoucle2.indexIn(ligne) != -1 && dansBoucle2 )
    {
        var = rxBoucle2.capturedTexts()[1];
        listeVar = rxBoucle2.capturedTexts()[2];
        indiceVar = rxBoucle2.capturedTexts()[3];
        signe = rxBoucle2.capturedTexts()[4];
        comp = rxBoucle2.capturedTexts()[5];
        listeComp = rxBoucle2.capturedTexts()[6];
        indiceListeComp = rxBoucle2.capturedTexts()[7];
    }
    else
    {
        return -1;
    }
    res=0;
    if (signe == "==")
    {

        if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
        {
            if(NbVar.contains(var))
            {

                if(NbVal[NbVar.indexOf(var)].toDouble() == QVariant(execOp(comp)).toDouble())
                {
                    res= 1;
                }
                else
                {
                    res= 0;
                }
            }
            else if(QRegExp(def_rxValListe).exactMatch(var))
            {
                if(recupValListe(var) == QVariant(execOp(comp)))
                { res= 1;}
                else
                { res= 0;}
            }
            else if(TxVar.contains(var))
            {
                if(TxVal[TxVar.indexOf(var)] == QVariant(execOp(comp)))
                { res= 1;}
                else
                {res= 0;}
            }
        }

    }
    else if (signe == "!=")
    {
        if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
        {
            if(NbVar.contains(var))
            {
                if(NbVal[NbVar.indexOf(var)] != QVariant(execOp(comp)))
                    res= 1;
                else
                    res= 0;
            }
            else if(QRegExp(def_rxValListe).exactMatch(var))
            {
                if(recupValListe(var) != QVariant(execOp(comp)))
                    res= 1;
                else
                    res= 0;
            }
            else if(TxVar.contains(var))
            {
                if(TxVal[TxVar.indexOf(var)] != QVariant(execOp(comp)))
                    res= 1;
                else
                    res= 0;
            }

        }

    }
    else if (signe == "<=")
    {
        if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
        {
            if(NbVar.contains(var))
            {
                if(NbVal[NbVar.indexOf(var)].toDouble() <= QVariant(execOp(comp)).toDouble())
                    res= 1;
                else
                    res= 0;
            }
        }
    }
    else if (signe == ">=")
    {
        if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
        {
            if(NbVar.contains(var))
            {
                if(NbVal[NbVar.indexOf(var)].toDouble() >= QVariant(execOp(comp)).toDouble())
                    res= 1;
                else
                    res= 0;
            }
        }
    }
    else if (signe == "<")
    {
        if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
        {
            if(NbVar.contains(var))
            {
                if(NbVal[NbVar.indexOf(var)].toDouble() < QVariant(execOp(comp)).toDouble())
                    res= 1;
                else
                    res= 0;
            }
        }
    }
    else if (signe == ">")
    {
        if(QRegExp("[()0-9+\\-/.*a-zA-Z_]+").exactMatch(comp))
        {
            if(NbVar.contains(var))
            {
                if(NbVal[NbVar.indexOf(var)].toDouble() > QVariant(execOp(comp)).toDouble())
                    res= 1;
                else
                    res= 0;
            }
        }
    }


    return res;
}

void FenPrincipale::affOptions()
{
    QSettings param;
    if(param.value("premOuverture",true).toBool())
    {
        if(QMessageBox::warning(this,"Valeurs initialisées","Il semble que vous avez réinitialisé les valeurs des options d'AlgoCreator.\nPour acceder aux options, vous devez redemarrer AlgoCreator.\nVoulez-vous l'arreter maintenant ?",QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
        {
            close();
        }
    }
    else
    {
        fenoptions fen(this);
        fen.exec();
        param.beginGroup("rxLang");
        rxLigne = QRegExp(param.value("rxLigne").toString());
        //Definition de la déclaratio  fichier.write();n d'un nombre
        rxNbVar =  QRegExp(param.value("rxVarNb").toString());
        //Definition de la déclaration d'une chaîne
        rxTxVar = QRegExp(param.value("rxVarTx").toString());
        //Définition de la déclaration d'une liste
        rxLsVar = QRegExp(param.value("rxVarLs").toString());


        rxModifListe = QRegExp(param.value("rxModLs").toString());
        rxRecupValListe = QRegExp(param.value("rxRecValLs").toString());
        rxRecupSaisie = QRegExp(param.value("rxRecSai").toString());
        rxVarOpSurSoisMeme = QRegExp(param.value("rxModOpSMM").toString());
        rxCondition = QRegExp(param.value("rxStrCondition").toString());
        rxBoucle = QRegExp(param.value("rxStrBoucle").toString());

        param.endGroup();
    }
}

void FenPrincipale::ouvrir()
{
    QString cheminAlgo = QFileDialog::getOpenFileName(this,"Selectionnez un algorithme à charger...",QString(),"Algorithme (*.algcrt);;Texte (*.txt);;Indéterminé (*.algcrt , *.txt);;Autre (*.*)");
    if (cheminAlgo != QString())
    {
        QFile fichier(cheminAlgo);

        if (fichier.exists())
        {
            if(fichier.open(QIODevice::ReadOnly))
            {

                QFileInfo fi(fichier);
                nom_fichier = fi.fileName();
                chemin_fichier = cheminAlgo;
                changeTitreFen(this,nom_fichier);
                zoneTexte->setText(fichier.readAll());
                fichier.close();

            }
            else
            {
                alerte(this,"Impossible d'ouvrir le ficher",QString("Le fichier\n"+cheminAlgo+"\nN'a pas pu être ouvert..."));
            }
        }
        else
        {
            alerte(this,"Impossible d'ouvrir le ficher",QString("Le fichier\n"+cheminAlgo+"\nN'existe pas...\nSi vous avez tapé manuellement le nom du fichier, verifiez que vous n'avez pas fait de fautes..."));
        }
    }
}

void FenPrincipale::sauvegarder()
{
    qDebug() << "Sauvegarde de l'Algorithme...";
    QString cheminAlgo = QFileDialog::getSaveFileName(this,"Sauvegarde d'un algorithme",chemin_fichier,"Algorithme (*.algcrt);;Texte (*.txt);;Indéterminé (*.algcrt , *.txt);;Autre (*.*)",new QString(),QFileDialog::DontConfirmOverwrite);
    qDebug() << "\tChemin : " << cheminAlgo ;
    if (cheminAlgo != QString())
    {
        QFile fichier(cheminAlgo);
        QFileInfo fi(fichier);
        QString nom = fi.fileName();

        if (fichier.exists() && nom != nom_fichier && ! ouiNon(this,"Ce fichier existe déjà, voulez vous l'écraser ?") )
        {
            qDebug() << "\tNon écrasement demandé...\nFichier non sauvé";
            sauvegarder();
        }
        else
        {
            if(fichier.open(QIODevice::WriteOnly|QIODevice::Truncate))
            {
                qDebug() << "\tFichier créé / écrasé";
                QTextStream(&fichier) << zoneTexte->text();


                chemin_fichier = cheminAlgo;
                nom_fichier = nom;

                qDebug() << "\tRafraichissement du titre de la fenetre..."
                         <<"\n\t\tNom du fichier : " << nom_fichier;

                changeTitreFen(this,nom_fichier);
                fichier.close();
                info(this,"Le fichier a bien été sauvegardé !");

            }
            else
            {
                alerte(this,"Impossible d'ouvrir le ficher",QString("Le fichier\n"+cheminAlgo+"\nN'a pas pu être ouvert..."));
            }
        }
    }
}



void FenPrincipale::nouveau()
{
    if(zoneTexte->text().contains("[^ \\n]") && ! ouiNon(this,"Un agorithme semble avoir été créé, il sera effacé...\nSi vous voulez le conserver, il vous suffit de le sauvegarder.\nVoulez-vous créer un nouvel algorithme ?"))
    {}
    else
    {
        zoneTexte->clear();
        nom_fichier = "Sans Titre";
        chemin_fichier = "";
        changeTitreFen(this,nom_fichier);
    }
}
