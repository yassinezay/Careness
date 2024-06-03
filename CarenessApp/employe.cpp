#include "employe.h"
#include <QCryptographicHash>
#include <QCoreApplication>

void employe::encrypt(QString &str) {
    for (int i = 0; i < str.length() && str[i] != '\0'; i++) {
         str[i] = QChar(str[i].toLatin1() + 2);
    }
   
}



void employe::decrypt(QString &str) {
    for (int i = 0; i < str.length() && str[i] != '\0'; i++) {
         str[i] = QChar(str[i].toLatin1() - 2);
    }
}



employe::employe(){
    id=0;
    nom="";
    prenom="";
    adresse="";
    designation="";
    cin=0;
    gender="";
    mdp="";
    num=0;
}

employe::employe(int id ,QString nom, QString prenom , QString gender ,int cin , QString designation ,QString adresse , QString mdp, int num)

{
    this->id=id;
    this->nom=nom;
    this ->prenom=prenom;
    this->adresse=adresse;
    this->cin=cin;
    this->designation=designation;
    this->mdp=mdp;
    this->gender=gender;
    this->num=num;

}

bool employe::ajouter(){

    QString id_string=QString::number(id);
    QString CIN_string=QString::number(cin);
    QString NUM_string=QString::number(num);

    QSqlQuery query;

         query.prepare("INSERT INTO employe (id, nom, prenom, gender,cin,designation,adresse, mdp , num) "
                       "VALUES (:id, :nom, :prenom,:gender,:cin ,:designation,:adresse , :mdp, :num)");
         query.bindValue(":id", id_string);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
         query.bindValue(":gender", gender);
         query.bindValue(":cin", CIN_string);
         query.bindValue(":designation", designation);
         query.bindValue(":adresse", adresse);

         query.bindValue(":mdp", mdp);
         query.bindValue(":num", NUM_string);



     return     query.exec();

}

QSqlQueryModel * employe::afficher(){

    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Designation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mdp"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));


    return model;
}

bool employe::supprimer(int id){
    QSqlQuery query;
          query.prepare("DELETE from employe where id=:id ");
          query.bindValue(":id", id);
      return     query.exec();
}

bool employe::modifier(int id)
{

QSqlQuery query;


QString id_string=QString::number(id);
QString CIN_string=QString::number(cin);

query.prepare("UPDATE employe SET nom=:nom,prenom=:prenom,gender=:gender,cin=:cin,designation=:designation,adresse=:adresse, mdp=:mdp, num=:num WHERE id=:id;");

     query.bindValue(":id",id_string);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
      query.bindValue(":gender", gender);
     query.bindValue(":cin", CIN_string );
     query.bindValue(":adresse", adresse );
     query.bindValue(":designation", designation );
     query.bindValue(":mdp", mdp);
     query.bindValue(":num", num);



return    query.exec();
}


//Recherche de données
bool employe::recherche(int id)
{
    QSqlQuery query;
    int c=0;
    query.prepare("SELECT * from employe where id=:id");
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




bool employe::recherche_login(QString adresse , QString mdp)
{
    QSqlQuery query;
    int c=0;
    query.prepare("SELECT * from employe where adresse=:adresse and mdp=:mdp");
    query.bindValue(":adresse",adresse);
    query.bindValue(":mdp",mdp);
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


bool employe::recherche_adresse(QString adresse)
{
    QSqlQuery query;
    int c=0;
    query.prepare("SELECT * from employe where adresse=:adresse ");
    query.bindValue(":adresse",adresse);

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


bool employe::recherche_designation(QString adresse)
{
    QSqlQuery query;
    int c=0;

    query.prepare("SELECT * from employe where adresse=:adresse ");
    query.bindValue(":adresse",adresse);


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

QSqlQueryModel * employe::tri(QString type)
{
QSqlQueryModel * model= new QSqlQueryModel();
QString ID="ID";
QString Nom="Nom";

if(type==ID){
    model->setQuery("SELECT * FROM employe order by ID ASC ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Designation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mdp"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));
}else
{
    model->setQuery("SELECT * FROM employe order by NOM ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Designation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mdp"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));

}



return model;
}

QSqlQueryModel * employe::afficherRSp(QString id)
{
    QSqlQuery query;

 QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe WHERE (NOM LIKE '%"+id+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Designation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mdp"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));


    return model;

}

QSqlQueryModel * employe::recherchep2(QString a)
{
QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employe WHERE ID LIKE '%"+a+"%' OR NOM LIKE '%"+a+"%' OR Prenom LIKE '%"+a+"%'  OR gender LIKE '%"+a+"%' OR CIN LIKE '%"+a+"%'" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Gender"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Designation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mdp"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Num"));




    return model;}
