#include "enfants.h"
#include <QObject>
#include <QtDebug>
#include <QMessageBox>
#include <QDateTime>


enfants::enfants()
{
id=0 ;
nom="";
prenom="";
age=0;


}

enfants::enfants(int id,QString nom,QString prenom,int age,QDate Date_de_naissance)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->age=age;
    this->Date_de_naissance=Date_de_naissance;
}

bool enfants::ajouter()
{



QString id_string=QString::number(id);
QString age_string=QString::number(age);
QSqlQuery query;

     query.prepare("INSERT INTO ENFANT (id, nom,prenom,age,date_de_naissance) "
                   "VALUES (:id, :forename, :prenom, :age, :date)");
     query.bindValue(":id", id_string);
     query.bindValue(":forename", nom);
     query.bindValue(":prenom", prenom);
     query.bindValue(":age", age_string);
     query.bindValue(":date", Date_de_naissance);


 return     query.exec();

}
QSqlQueryModel * enfants::afficher()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("SELECT * FROM ENFANT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date De Naissance"));



return model;
}

bool enfants::recherche(int id)
{
    QSqlQuery query;
    int c=0;
    query.prepare("SELECT * from ENFANT where id=:id");
    query.bindValue(":id",id);
    if(query.exec())
    {
        while(query.next())
        {
            c++;
        }

        if(c==1)
        {
            QMessageBox boxt;
            boxt.setText("trouvé");
            return true;

        }


    }
    return false;

}
bool enfants::supprimer(int id)
{

    QSqlQuery query;

         query.prepare("DELETE from enfant where id=:id ");
         query.bindValue(":id", id);
     return     query.exec();

}
QSqlQueryModel * enfants::tri(QString type)
{
QSqlQueryModel * model= new QSqlQueryModel();
QString age="age";
QString id="id";
if(type==id){
    model->setQuery("SELECT * FROM enfant order by id DESC ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date De Naissance"));

}else
{
    model->setQuery("SELECT * FROM enfant order by age DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date De Naissance"));

}



return model;
}
bool enfants::modifier(int id)
{

QSqlQuery query;


QString id_string=QString::number(id);

query.prepare("UPDATE ENFANT SET nom=:nom,prenom=:prenom,age=:age,Date_de_naissance=:Date_de_naissance WHERE id=:id;");

query.bindValue(":id",id_string);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":age",age);

     query.bindValue(":Date_de_naissance", Date_de_naissance );

return    query.exec();
}
QSqlQueryModel * enfants::afficherRSp(QString id)
{
    QSqlQuery query;

 QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM enfant WHERE (nom LIKE '%"+id+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date De Naissance"));

    return model;

}

