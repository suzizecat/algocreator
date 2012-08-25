#-------------------------------------------------
#
# Project created by QtCreator 2012-05-06T20:06:16
#
#-------------------------------------------------

QT       += core gui

TARGET = AlgoCreator
TEMPLATE = app


SOURCES += main.cpp\
        fenprincipale.cpp \
    fenoptions.cpp \
    qscilexeralgo.cpp \
    gestionAffichage.cpp \
    assistfonctionsvarsimples.cpp \
    assistfonctionsconditions.cpp \
    assistcreationvar.cpp \
    assistfonctionhasard.cpp

HEADERS  +=  fenprincipale.hpp \
    fenoptions.hpp \
    qscilexeralgo.hpp \
    gestionAffichage.hpp \
    assistfonctionsvarsimples.hpp \
    assistfonctionsconditions.hpp \
    assistcreationvar.hpp \
    assistfonctionhasard.hpp

FORMS    += fenprincipale.ui \
    fenoptions.ui \
    assistfonctionsvarsimples.ui \
    assistfonctionsconditions.ui \
    assistcreationvar.ui \
    assistfonctionhasard.ui
LIBS += -lqscintilla2

OTHER_FILES += \
    langage.api

RESOURCES += \
    ressources.qrc
