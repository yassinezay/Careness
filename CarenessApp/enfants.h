#ifndef ENFANTS_H
#define ENFANTS_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QDate>
class enfants
{
    QString nom,prenom;
       QDate Date_de_naissance;

       int id,age;
   public:
       enfants();
       enfants(int,QString,QString,int,QDate);
       QString getnom(){return nom;}
       int getage(){return age ;}
       QString getprenom(){return prenom ;}
       QDate getdate(){return Date_de_naissance;}
       int getid(){return id;}
       void setnom(QString n){nom=n;}
       void setprenom(QString p){prenom=p;}
       void setid(int id){this->id=id;}
       void setage(int a){age=a;}
       void setdate(QDate d){ Date_de_naissance=d ;}
       bool rechercher(int id);
       bool ajouter();
       QSqlQueryModel * afficher();
       bool supprimer(int id);
       bool recherche(int id);
       QSqlQueryModel * tri(QString type);
       bool modifier(int id);
       QSqlQueryModel * afficherRSp(QString id);
        QSqlQueryModel * tri(int id);



};

#endif // ENFANTS_H
