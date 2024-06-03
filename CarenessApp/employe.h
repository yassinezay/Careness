#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQuery>
#include <QMessageBox>
#include<QSqlQueryModel>
#include <string>



class employe
{
    QString nom,prenom,adresse, designation , gender, mdp;
    int id,cin,num;
public:
    //Constructeur
    employe();
    employe(int ,QString,QString,QString , int ,QString,QString, QString,int);

    //Getters
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    int getID(){return id;}
    QString getAdresse(){return adresse;}
    QString getdesi(){return designation;}
    int getcin(){return cin;}
    QString getmdp(){ return mdp;}
    QString getgenre(){ return gender;}
    int getnum(){return num;}



    //Setters
    void setNom(QString n ){nom=n;}
    void setPrenom(QString n){prenom=n;}
    void setID (int id ){this->id=id; }
    void setdesi(QString n ){designation=n;}
    void setadresse(QString n){adresse=n;}
    void setmdp(QString n){mdp=n;}
    void setgenre(QString n){gender=n;}
    void setnum(int num){this->num=num;}
    void setcin (int cin ){this->cin=cin; }


    //Fonctions
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int );
    bool recherche(int);
    bool recherche_login(QString , QString);
    bool recherche_adresse(QString);
    bool recherche_designation(QString);
    QSqlQueryModel * tri(QString type);
    QSqlQueryModel * afficherRSp(QString);
    QSqlQueryModel * recherchep2(QString);
    void encrypt(QString &str) ;
    void decrypt(QString &str) ;




};

#endif // EMPLOYE_H
