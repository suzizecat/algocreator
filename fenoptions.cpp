#include "fenoptions.hpp"

fenoptions::fenoptions(QWidget *parent) : QDialog(parent)
{


    setupUi(this);
    vidageVar->setVisible(false);
    modelRegexTable = new QStandardItemModel(10,2);

    affVar();

    connect(boutonsQuitter,SIGNAL(accepted()),this,SLOT(sauveEtQuitte()));
    connect(initValDef,SIGNAL(clicked()),this,SLOT(initVal()));

}


void fenoptions::initVal()
{
    if(QMessageBox::question(this,"Confirmation",
                             "Voulez-vous vraiment réinitialiser tous les paramètres avec leur valeur d'origine ?\nAttention, cette action n'est pas annulable...",
                             QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
    {
        param.setValue("premOuverture",true);
        QMessageBox::information(this,"AlgoCreator","Tous les paramètres ont été réinitialisés.\nPour mettre ces changements en application, vous devez redémarrer AlgoCreator.");
        close();
    }
}

bool fenoptions::sauveParam()
{
    param.beginGroup("rxLang");

            int i;
            QMessageBox::information(this,"Info","Sauvegarde des parametres...");
           vidageVar->setText(modelRegexTable->index(i,0).data().toString()+modelRegexTable->index(i,1).data().toString());
        while(modelRegexTable->index(i,0).data().toString() != "" )
        {
           param.setValue(modelRegexTable->index(i,0).data().toString(),modelRegexTable->index(i,1).data().toString());

            i++;
        }

        affVar();
    param.endGroup();



}

void fenoptions::affVar()
{

    param.beginGroup("rxLang");
    QStringList cles = param.allKeys();
    int pos = 0;
    for (int i=0 ; i < cles.length(); i++)
    {
        QStandardItem *StdI =new QStandardItem(cles[i]);
        StdI->setEditable(false);
        modelRegexTable->setItem(i, 0, StdI);
        modelRegexTable->setItem(i, 1, new QStandardItem(param.value(cles[i],"").toString()));
    }
    RegExpView->setModel(new QStandardItemModel);
    RegExpView->setModel(modelRegexTable);
    param.endGroup();

}

void fenoptions::sauveEtQuitte()
{
    sauveParam();
    close();
}
