#include "login.h"
#include "ui_login.h"
#include <QStackedWidget>
#include <QIntValidator>
#include <QMessageBox>
#include <QDate>
#include<QRegExp>
#include<QTextEdit>
#include<QSqlTableModel>
#include "employe.h"
#include<QDebug>
#include <string>
#include "arduino.h"


Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    employe e;
    ui->setupUi(this);
    ui->Attention->setVisible(false);
    ui->Attention_2->setVisible(false);
    ui->Gender_label->setVisible(false);
    ui->ID_3->setValidator( new QIntValidator(100, 99999999, this));
    ui->cin_4->setValidator( new QIntValidator(100, 99999999, this));
    ui->Tel_2->setValidator( new QIntValidator(100, 99999999, this));
    animation = new QPropertyAnimation(ui->bienvenu, "geometry");
    animation->setDuration(15000);
    animation->setStartValue(ui->bienvenu->geometry());
    animation->setEndValue(QRect(500,500,100,200));
    animation->setLoopCount(-1); // boucle en continu
    animation->start();
    animation2 = new QPropertyAnimation(ui->careness, "pos");
    animation2->setDuration(5000);
    animation2->setStartValue(QPoint(-140, 30));
    animation2->setEndValue(QPoint(480, 30));
    animation2->setLoopCount(-1); // boucle en continu
    animation2->start();

}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Login::on_connect_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
//bouton login
void Login::on_pushButton_4_clicked()
{
    QSqlQuery query;

    employe e;
    QString  adresse = ui->Email->text();
    QString mdp = ui->mdp->text(),h;

    e.encrypt(mdp);

    e.setadresse(adresse);
    e.setmdp(mdp);
    QRegExp Exp_mail ("^[\\w|\\.]+@[\\w]+\\.[\\w]{2,4}$");
    QRegExp Exp_mdp ("^(?=.*[A-Za-z])(?=.*[0-9])[A-Za-z0-9]{8,}$");
    bool value=true;
    //controle de saisie du mail et mdp





        query.prepare("SELECT * FROM employe WHERE adresse = :adresse AND mdp =:mdp ");
        query.bindValue(":adresse", adresse);
               query.bindValue(":mdp", mdp);
               QString D;
               query.exec();

                       if (query.first()) {



                this->hide();
                MainWindow *m = new MainWindow;
                D=query.value(4).toString();
QString   nom=query.value(1).toString();
QString   PRENOM=query.value(2).toString();
QString   NUM=query.value(7).toString();
QString   cin=query.value(3).toString();
QString   G=query.value(8).toString();
                m->setUserInfo(D, NUM,nom,PRENOM,adresse,cin,G);
                m->show();
                QMessageBox::information(this, "Se connecter", "Bienvenue   " +query.value(1).toString() );


            //Affichage des données dans la page profil




}else {
           QMessageBox::warning(this, "Erreur", "Nom d'utilisateur ou mot de passe incorrect.");
        }

}


void Login::on_pushButton_10_clicked()
{
    QMessageBox msgbox;
    QString  adresse = ui->email_2->text();
    QString mdp = ui->mdp_2->text();
    QString mdpc = ui->mdp_3->text();
    int val= mdp.compare(mdpc);
    QRegExp Exp_mail ("^[\\w|\\.]+@[\\w]+\\.[\\w]{2,4}$");
    QRegExp Exp_mdp ("^(?=.*[A-Za-z])(?=.*[0-9])[A-Za-z0-9]{8,}$");
    bool value=true;


    if (adresse.contains(Exp_mail)==false){
        QMessageBox::critical (this, "Validation", " Adresse  n'est pas valide !");
        value=false;
    }

    if (mdp.contains(Exp_mdp)==false){
        QMessageBox::critical (this, "Validation", " Mot de passe n'est pas valide !  Doit commencer avec une Majus avec l'exitance d'un chiffre");
        value=false;

    }

    employe e;
    if(value==true)
    {
    e.setadresse(ui->email_2->text());
    if(e.recherche_adresse(e.getAdresse()))
    {
        QMessageBox::critical (this, "Validation", " Veuillez entrer un nom d'utilisateur valide ! !");

    }else if (!(val==0)){
        QMessageBox::critical (this, "Validation", " Mot de passe incorrecte!");


    }else{

        ui->stackedWidget->setCurrentIndex(2);

    }
    }
}

void Login::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}

void Login::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Login::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Login::on_pushButton_14_clicked()
{
    QMessageBox msgbox;

    QString adresse=ui->email_2->text();

    QString mdp=ui->mdp_2->text();
    employe e1;
    e1.encrypt(mdp);
    int id=ui->ID_3->text().toInt();
     QString nom=ui->Nom_2->text();
     QString prenom=ui->Prenom->text();
     if (ui->radioButton_3->isChecked()){
         ui->Gender_label->setText(ui->radioButton_3->text());
     }else{ ui->Gender_label->setText(ui->radioButton_4->text());}
     QString gender=ui->Gender_label->text();

     int cin=ui->cin_4->text().toInt();
     QString designation=ui->desi_4->currentText();
     int num = ui->Tel_2->text().toInt();

     employe e(id , nom , prenom, gender , cin , designation, adresse, mdp , num);

     e.setID(ui->ID_3->text().toInt());
     e.encrypt(mdp);
     if(e.recherche(e.getID()))
     {
     msgbox.setText("erreur");
    }else
     {
     bool test=e.ajouter();

         if(test){
             msgbox.setText("Ajouter avec succes");
             ui->stackedWidget->setCurrentIndex(0);


         }
    }
        msgbox.exec();
}
