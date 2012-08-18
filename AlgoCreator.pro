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
    gestionAffichage.cpp

HEADERS  +=  fenprincipale.hpp \
    fenoptions.hpp \
    qscilexeralgo.hpp \
    gestionAffichage.hpp

FORMS    += fenprincipale.ui \
    fenoptions.ui
LIBS += -lqscintilla2

OTHER_FILES += \
    langage.api
