#ifndef GESTIONAFFICHAGE_HPP
#define GESTIONAFFICHAGE_HPP
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QWidget>
#include <QCoreApplication>

void info(QWidget *parent, QString contenu);
void info(QWidget *parent,QString titre ,QString contenu);

void avertissement(QWidget *parent, QString contenu);
void avertissement(QWidget *parent,QString titre ,QString contenu);

void alerte(QWidget *parent, QString contenu);
void alerte(QWidget *parent,QString titre ,QString contenu);


bool ouiNon(QWidget *parent, QString contenu);
bool ouiNon(QWidget *parent,QString titre ,QString contenu);

void changeTitreFen(QWidget *parent, QString titre,bool titreComplet=false);

QString intVersStr(int nombre);
#endif // GESTIONAFFICHAGE_HPP
