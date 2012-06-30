#include <QtGui/QApplication>
#include "fenprincipale.hpp"

#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include <QTextCodec>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Amidemoi");
    app.setApplicationName("AlgoCreator");
    app.setApplicationVersion("0.2 BETA");
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //Pour activer l'encodage UTF-8 sur les boites de dialogue
    FenPrincipale principale;
    principale.setWindowIcon(QIcon("/usr/share/icons/hicolor/128x128/apps/algocreator.png"));
    principale.setWindowTitle("AlgoCreator v"+app.applicationVersion());
    principale.show();
    return app.exec();
}
