#include "stock.h"
#include <QObject>
#include <QtDebug>
#include <QMessageBox>
#include<QDate>
stock::stock()
{
id=0 ;
nom=" ";
quantite="0";
type=" ";
}

stock::stock(int id,QString nom,QString prenom,QString type,QDateTime d)
{
    this->id=id;
    this->nom=nom;
    this->quantite=prenom;
    this->type=type;
    this->d=d;
}

bool stock::ajouter()
{

QString id_string=QString::number(id);
QSqlQuery query;

     query.prepare("INSERT INTO STOCK (id, nom,quantite,type,dates) "
                   "VALUES (:id, :forename, :surname, :type, :date)");
     query.bindValue(":id", id_string);
     query.bindValue(":forename", nom);
     query.bindValue(":surname", quantite);
     query.bindValue(":type", type);
     query.bindValue(":date", d);

 return     query.exec();

}

QSqlQueryModel * stock::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM stock ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
    return model;



}

bool stock::supprimer(int id)
{

    QSqlQuery query;

         query.prepare("DELETE from stock where id=:id ");
         query.bindValue(":id", id);
     return     query.exec();

}
bool stock::recherche(int id)
{
    QSqlQuery query;
    int c=0;
    query.prepare("SELECT *from stock where id=:id");
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


QSqlQueryModel * stock::tri(QString type)
{
QSqlQueryModel * model= new QSqlQueryModel();
QString date="Date";
QString id="Nom";

if(type==date){
    model->setQuery("SELECT * FROM stock order by dates DESC ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
}else
{
    model->setQuery("SELECT * FROM stock order by id DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
}



return model;
}
bool stock::modifier(int id)
{

QSqlQuery query;


QString id_string=QString::number(id);

query.prepare("UPDATE stock SET nom=:nom,type=:type,quantite=:quantite,dates=:dates WHERE id=:id;");

query.bindValue(":id",id_string);
     query.bindValue(":nom",nom);
     query.bindValue(":type",type);
     query.bindValue(":quantite", quantite );
     query.bindValue(":dates", d );

return    query.exec();
}

QSqlQueryModel * stock::afficherRS(QString id)
{
    QSqlQuery query;

 QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM stock WHERE (nom LIKE '%"+id+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));

    return model;

}
QSqlQueryModel * stock::recherches2(QString a)
{
QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from stock WHERE id LIKE '%"+a+"%' OR nom LIKE '%"+a+"%' OR quantite LIKE '%"+a+"%'  OR type LIKE '%"+a+"%' OR dates LIKE '%"+a+"%'" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));



    return model;}

int stock::compteur(int a)
{
    QSqlQuery query;
    query.prepare("SELECT SUM(quantite) FROM STOCK WHERE EXTRACT(YEAR FROM dates) = :a ");
    query.bindValue(":a", a);
    if (query.exec() && query.next()) {
        int numRows = query.value(0).toInt();
        return numRows;
    }else
    {
        return  0;
    }
}
int stock::compteur1()
{
    QSqlQuery query;
   query.prepare("SELECT SUM(quantite) FROM stock");
    if (query.exec() && query.next()) {
        int numRows = query.value(0).toInt();
        return numRows;
    }else
    {
        return  0;
    }
}
