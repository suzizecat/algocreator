#include <QtGui/QApplication>
#include "fenprincipale.hpp"

#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include <QTextCodec>


int main(int argc, char *argv[])
{
     qDebug() << "Lancement du programme ...";
    QApplication app(argc, argv);
    app.setOrganizationName("Amidemoi");
    app.setApplicationName("AlgoCreator");
    app.setApplicationVersion("0.42 BETA");
    qDebug() <<"Organisation : " << app.organizationName() << "\nNom du programme : "
             << app.applicationName() << "\nVersion : " << app.applicationVersion() << "\nChemin du programme :"
                << app.applicationDirPath();
    qDebug() << "Mise en place de la traduction et de l'encodage ...";
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //Pour activer l'encodage UTF-8 sur les boites de dialogue
    qDebug() << "Langue : " << locale ;

    qDebug() << "Initialisation des nombres aleatoires...";
    qsrand(QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz").toInt());
    qDebug()<<"\tGraine : " << QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
    qDebug() << "Creation de la fenetre principale...";
    FenPrincipale principale;
#ifdef Q_OS_LINUX
    principale.setWindowIcon(QIcon("/usr/share/icons/hicolor/128x128/apps/algocreator.png"));
#endif
    principale.setWindowTitle("AlgoCreator v"+app.applicationVersion());
    principale.show();
    qDebug() << "Progamme lance !";
    return app.exec();
}
