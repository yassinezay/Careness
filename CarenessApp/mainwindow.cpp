#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include "partenaire.h"
#include "stock.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDate>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include "notification.h"
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>
#include <QUrl>
#include <QDesktopServices>
#include <QDebug>
#include "smtp.h"
#include <QAbstractTableModel>
#include <QObject>
#include <QStandardItemModel>
#include "event.h"
#include <QTimer>
#include <QDateTime>
#include <QPixmap>
#include "enfants.h"
#include <qrcode.h>
#include <QtNetwork>
#include <QTranslator>
#include <QInputDialog>
#include "employe.h"
#include "login.h"
#include <QQuickItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_currentPage = 0;
    partenaire p;
    stock e;
    Event E;
    enfants ee;
    employe emp;


    ui->setupUi(this);
    ui->Gender_label_2->setVisible(false);
    ui->id->setValidator( new QIntValidator(100, 9999999, this));
    ui->idp->setValidator( new QIntValidator(100, 9999999, this));
    ui->tabstock->setModel(e.afficher());
    ui->tabpartenaire->setModel(p.afficher());
    ui->listView->setModel(p.afficher_historique0());
    ui->TABRECHS->setModel(e.afficher());
    ui->tabarduino->setModel(A.afficher_arduino());
    ui->idE->setValidator( new QIntValidator(100, 9999999, this));
    ui->id2->setValidator( new QIntValidator(100, 9999999, this));
 ui->age->setValidator( new QIntValidator(100, 9999999, this));
 ui->idsupprim_2->setValidator( new QIntValidator(100, 9999999, this));
ui->IDemp->setValidator( new QIntValidator(100, 9999999, this));
ui->cinemp->setValidator( new QIntValidator(100, 9999999, this));
ui->Telemp->setValidator( new QIntValidator(100, 9999999, this));
ui->tabenfants->setModel(ee.afficher());
    ui->tabevent->setModel(E.afficher());
    ui->tabarduino_2->setModel(A.afficher_arduino2());
    ui->tableemploye_2->setModel(emp.afficher());

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();
    animation = new QPropertyAnimation(ui->bienvenu, "geometry");
    animation->setDuration(15000);
    animation->setStartValue(ui->bienvenu->geometry());
    animation->setEndValue(QRect(1500,700,200,500));
    animation->setLoopCount(-1); // boucle en continu
    animation->start();

    //ui->centralwidget->setStyleSheet("Qcentralwidget{ image: url(:/new/prefix1/images/BQCK.png);}");
    //maps

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    ui->quickWidget->show();

    auto obj = ui->quickWidget->rootObject();
    connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
    connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

    emit setCenter(30.000, 50.000);
    emit addMarker(25.000, 50.000);


     setCamera(QCameraInfo::defaultCamera());

     QMediaPlayer *player = new QMediaPlayer;
     QVideoWidget *videoWidget = new QVideoWidget(ui->frame_16);

     // Set the video output for the player to the video widget
     player->setVideoOutput(videoWidget);

     // Set the media to the video file you want to play
     QUrl videoUrl = QUrl::fromLocalFile("C:/Users/MSI/Desktop/CARNESSfinal/CarenessApp/images/videoplayback (1).mp4");
     player->setMedia(videoUrl);
     videoWidget->setGeometry(0, 0,ui->frame_16->width(), ui->frame_16->height());

     // Create a layout for the video widget and add it to the frame
     QVBoxLayout *layout = new QVBoxLayout(ui->frame_16);
     layout->addWidget(videoWidget);
     ui->frame_16->setLayout(layout);

     // Start playing the video
     player->play();

     connect(player, &QMediaPlayer::stateChanged, [=](QMediaPlayer::State newState) {
         // If the player state is StoppedState, restart the video
         if (newState == QMediaPlayer::StoppedState) {
             player->play();
         }
     });




}
QString MainWindow::setUserInfo(const QString& desegnation, const QString& num, const QString& nom, const QString& prenom , const QString& adresse, const QString& cin , const QString& gender){

   QString numero =num;
   QString fname =nom;
   QString d=desegnation;
   QString lname =prenom;
   QString ad =adresse;
   QString c =cin;
   QString g =gender;

  ui->GG->setText(d);
  ui->GG_2->setText(fname);
  ui->GG_3->setText(lname);
  ui->GG_4->setText(ad);
  ui->GG_5->setText(numero);
  ui->GG_6->setText(g);
  ui->GG_7->setText(c);
   return d;

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showTime()
{
    QTime time=QTime ::currentTime();
    QString time_texte=time.toString("hh : mm : ss");
    if((time.second() % 2)==0)
    { time_texte[3]= ' ';
        time_texte[8]= ' ';
    }
    ui->digitalclock->setText(time_texte);
}
void MainWindow::on_btn_ogrenci_5_clicked()
{
    sound->play();

    ui->stackedWidgetbar->setCurrentIndex(2);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(1);
}

void MainWindow::on_btn_ogrenci_6_clicked()
{  sound->play();

    QString TYPE;
    TYPE = ui->GG->text();

                   if (TYPE=="Gestion_stock" || TYPE=="Admin") {


    ui->stackedWidgetbar->setCurrentIndex(0);
                   }else {
 QMessageBox::warning(this, "Erreur", "vous n'avez pas l'accés");    }

    }


void MainWindow::on_checkBox_3_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
}

void MainWindow::on_checkBox_4_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);

}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);

}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);

}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(1);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(1);
}
//gestion stock

void MainWindow::on_validers_clicked()
{
    QMessageBox msgbox;

    int id=ui->id->text().toInt();
    QString nom=ui->nomStock->text();
    QString prenom=ui->quantite->text();
    QString type=ui->typestock->text();
    QDateTime date=ui->dates->dateTime();
    QRegExp regex("^[A-Za-z]+$");
    QRegExp regex1("^[0-9]+$");


    stock p(id,nom,prenom,type,date);
    p.setid(ui->id->text().toInt());
    if (id < 0 || !id)
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme id"),
                    QObject::tr("verifier id\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if (!regex.exactMatch(nom))
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter un nom \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if ( !regex.exactMatch(type)  )
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter un type de stock !! \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if ( !regex1.exactMatch(prenom) )
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter le quantite  !! \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
  else
    {
   stock P(id,nom,prenom,type,date);
    p.setid(ui->id->text().toInt());
    if(p.recherche(p.getid()))
    {
    msgbox.setText("stock existe deja");
    }else
    {bool test=p.ajouter();

        if(test){
            msgbox.setText("ajouter avec succes");
        }
   }
        msgbox.exec();
    }
}

void MainWindow::on_supprstock_clicked()
{
    QMessageBox msgbox;
    int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que vous etes sur de supprimer cet stock ?", QMessageBox ::Yes | QMessageBox::No);

stock p;
p.setid(ui->idsupp->text().toInt());

    if (reponse == QMessageBox::Yes)
    {
        if(p.recherche(p.getid()))
        {
        bool test=p.supprimer(p.getid());
        if(test){
            msgbox.setText("suppression avec succes");
        }
        }else
        msgbox.setText("stock introuvable !!");
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::information(this, "Careness", "Annulation!");
    }


    msgbox.exec();
}

void MainWindow::on_pushButton_valid_10_clicked()
{
    stock e;
    ui->tabstock->setModel(e.afficher());
}

void MainWindow::on_modifierStock_clicked()
{
    QMessageBox msgbox;
    int id=ui->id->text().toInt();
    QString nom=ui->nomStock->text();
    QString prenom=ui->quantite->text();
    QString type=ui->typestock->text();
    QDateTime date=ui->dates->dateTime();
 stock e(id,nom,prenom,type,date);
    e.setid(ui->id->text().toInt());

   if(e.recherche(e.getid()))
   {
       bool test=e.modifier(id);
   if(test){
       msgbox.setText("modifier avec succes");
   }}else
   msgbox.setText("id introuvable!!");
       msgbox.exec();
}
void MainWindow::on_treeStock_clicked()
{
    stock s;
    QString type=ui->nomdetrii->currentText();
    ui->tabstock->setModel(s.tri(type));
}


void MainWindow::on_pushButton_valid_11_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(4);
}

void MainWindow::on_BRS_clicked()
{
    stock s;
    QString nom=ui->RECHERCHES->text();
     ui->TABRECHS->setModel(s.afficherRS(nom));
}

void MainWindow::on_BRS_2_clicked()
{
    stock s;
    QString nom=ui->RECHERCHES_2->text();
     ui->tabstock->setModel(s.afficherRS(nom));
}
//end gestion stock

//gestion partenaire

void MainWindow::on_validpartenaire_clicked()
{

    QMessageBox msgbox;
    notification n;
    int id=ui->idp->text().toInt();
    QString nom=ui->nomp->text();
    int quantite=ui->quantitep->text().toInt();
    QString type=ui->typep->text();
    QString somme=ui->sommep->text();
    QString numtel=ui->nump->text();
    QRegularExpression regex("^\\+216[0-9]{8}$");
    QRegExp regex1("^[A-Za-z]+$");
    QDateTime Date_convention = ui->date_partenaire->dateTime();
    if (id < 0 || !id)
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme id"),
                    QObject::tr("verifier id\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if (!regex1.exactMatch(nom))
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter un nom \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if ( type.isEmpty() && somme.isEmpty() )
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter un type de don !! \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if ( !regex.match(numtel).hasMatch() )
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter le numero de telephone correct avec +216 !! \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
  else
    {
    partenaire p(id,nom,numtel,type,quantite,somme,Date_convention);
    p.setid(ui->idp->text().toInt());


    if(p.recherche(p.getid()))
    {
    msgbox.setText("partenaire existe deja");
    }else
    {bool test=p.ajouter();

        if(test){

            msgbox.setText("ajouter avec succes");
            p.ajouter_historique("ajout",nom,id);
            ui->listView->setModel(p.afficher_historique0());
            n.notification_ajout();
            sound1->play();



        }
   }
        msgbox.exec();
    }
}

void MainWindow::on_pushButton_valid_16_clicked()
{
    partenaire p;
    ui->tabpartenaire->setModel(p.afficher());
}

void MainWindow::on_supp_partenaire_clicked()
{
    QMessageBox msgbox;
    int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que vous etes sur de supprimer cet partenaire ?", QMessageBox ::Yes | QMessageBox::No);

partenaire p;
p.setid(ui->idsupp_2->text().toInt());

    if (reponse == QMessageBox::Yes)
    {
        if(p.recherche(p.getid()))
        {
        bool test=p.supprimer(p.getid());
        if(test){
            msgbox.setText("suppression avec succes");
            p.ajouter_historique("suppression",ui->nomp->text(),ui->idp->text().toInt());
            ui->listView->setModel(p.afficher_historique0());


        }
        }else
        msgbox.setText("Partenaire introuvable !!");
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::information(this, "Careness", "Annulation!");
    }


    msgbox.exec();
}

void MainWindow::on_pushButton_valid_18_clicked()
{
    partenaire p;
    QString type=ui->selectri->currentText();
    ui->tabpartenaire->setModel(p.tri(type));

}

void MainWindow::on_selectri_activated(const QString &arg1)
{
    partenaire p;
}

void MainWindow::on_modifierp_clicked()
{
    QMessageBox msgbox;
    int id=ui->idp->text().toInt();
    QString nom=ui->nomp->text();
    int quantite=ui->quantitep->text().toInt();
    QString type=ui->typep->text();
    QString somme=ui->sommep->text();
    QString numtel=ui->nump->text();
    QDateTime Date_convention = ui->date_partenaire->dateTime();
    partenaire p(id,nom,numtel,type,quantite,somme,Date_convention);
    p.setid(ui->idp->text().toInt());

   if(p.recherche(p.getid()))
   {
       bool test=p.modifier(id);
   if(test){
       msgbox.setText("modifier avec succes");
       p.ajouter_historique("modification",nom,id);
       ui->listView->setModel(p.afficher_historique0());

   }}else
   msgbox.setText("id introuvable!!");
       msgbox.exec();
}



void MainWindow::on_btn_quitter_clicked()
{
    int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que tu veux quitter?", QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            QMessageBox::critical(this, "Careness", "A la prochaine !");
            close();
        }
        else if (reponse == QMessageBox::No)
        {
            QMessageBox::information(this, "Careness", "bienvenue!");
        }
}

void MainWindow::on_btn_gpartenaire_clicked()
{
    sound->play();
    QString TYPE;
        TYPE = ui->GG->text();

                       if (TYPE=="Gestion_partenaire" || TYPE=="Admin") {
        sound->play();

       ui->stackedWidgetbar->setCurrentIndex(3);
                       }else {
                QMessageBox::warning(this, "Erreur", "vous n'avez pas l'accés");
        }

        }



void MainWindow::on_btn_phistorique_clicked()
{

    ui->stackedWidgetbar->setCurrentIndex(5);

}

void MainWindow::on_btn_retourp_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(3);


}

void MainWindow::on_pushButton_valid_14_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}

void MainWindow::on_pushButton_valid_15_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);

}

void MainWindow::on_BRp_clicked()
{
    partenaire p;
    QString nom=ui->RECHERCHESp->text();
     ui->tabpartenaire->setModel(p.afficherRSp(nom));
}


void MainWindow::on_pushButton_6_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
            qDebug()<<dir;
            QPdfWriter pdf(dir+"/PdfList.pdf");
                                   QPainter painter(&pdf);
                                  int i = 4000;

                                        painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/Users/ASUS/Desktop/projetcppv5/images/Logo.png"));
                                       // painter.drawText(900,650,"Careness");
                                       painter.setPen(Qt::blue);
                                       painter.setFont(QFont("Time New Roman", 25));
                                       painter.drawText(3000,1400,"Liste des partenaire");
                                       painter.setPen(Qt::black);
                                       painter.setFont(QFont("Time New Roman", 15));
                                       painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                       painter.drawRect(100,3000,9400,500);
                                       painter.setFont(QFont("Time New Roman", 9));
                                       painter.drawText(300,3300,"ID");
                                       painter.drawText(2000,3300,"nb_emp");
                                       painter.drawText(4000,3300,"nb_borne");
                                       painter.drawText(5600,3300,"nom_responsable");
                                       painter.drawText(7200,3300,"localisation");

                                       painter.drawRect(100,3000,9400,10700);
                                       //QTextDocument previewDoc;
                                       QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                                       //QTextCursor cursor(&previewDoc);
                                       QSqlQuery query;
                                       query.prepare("select * from partenaire");
                                       query.exec();
                                       while (query.next())
                                       {
                                           painter.drawText(300,i,query.value(0).toString());
                                           painter.drawText(2000,i,query.value(1).toString());
                                           painter.drawText(4000,i,query.value(2).toString());
                                           painter.drawText(5600,i,query.value(3).toString());
                                           painter.drawText(7000,i,query.value(4).toString());
                                           painter.drawText(8000,i,query.value(5).toString());
                                          i = i +500;
                                       }
                                       int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                           QMessageBox::Yes|QMessageBox::No);
                                           if (reponse == QMessageBox::Yes)
                                           {
                                               QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                               painter.end();
                                           }
                                           else
                                           {
                                                painter.end();
                                           }
}

void MainWindow::on_pdfS_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
        qDebug()<<dir;
        QPdfWriter pdf(dir+"/PdfList.pdf");
                               QPainter painter(&pdf);
                              int i = 4000;

                                    painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/Users/MSI/Desktop/projetcppv5/images/Logo.png"));
                                   // painter.drawText(900,650,"Smart Charging Station");
                                   painter.setPen(Qt::blue);
                                   painter.setFont(QFont("Time New Roman", 25));
                                   painter.drawText(3000,1400,"Liste des STOCK");
                                   painter.setPen(Qt::black);
                                   painter.setFont(QFont("Time New Roman", 15));
                                   painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                   painter.drawRect(100,3000,9400,500);
                                   painter.setFont(QFont("Time New Roman", 9));
                                   painter.drawText(300,3300,"ID");
                                   painter.drawText(2000,3300,"QUANTITE");
                                   painter.drawText(4000,3300,"DATE");
                                   painter.drawText(5600,3300,"NOM");
                                   painter.drawText(7200,3300,"localisation");

                                   painter.drawRect(100,3000,9400,10700);
                                   //QTextDocument previewDoc;
                                   QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                                   //QTextCursor cursor(&previewDoc);
                                   QSqlQuery query;
                                   query.prepare("select * from STOCK");
                                   query.exec();
                                   while (query.next())
                                   {
                                       painter.drawText(300,i,query.value(0).toString());
                                       painter.drawText(2000,i,query.value(1).toString());
                                       painter.drawText(4000,i,query.value(2).toString());
                                       painter.drawText(5600,i,query.value(3).toString());
                                       painter.drawText(7000,i,query.value(4).toString());
                                       painter.drawText(8000,i,query.value(5).toString());
                                      i = i +500;
                                   }
                                   int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                       QMessageBox::Yes|QMessageBox::No);
                                       if (reponse == QMessageBox::Yes)
                                       {
                                           QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                           painter.end();
                                       }
                                       else
                                       {
                                            painter.end();
                                       }
}

void MainWindow::on_exitb_clicked()
{
    int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que tu veux quitter?", QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            QMessageBox::critical(this, "Careness", "A la prochaine !");
            close();
        }
        else if (reponse == QMessageBox::No)
        {
            QMessageBox::information(this, "Careness", "bienvenue!");
        }
}

void MainWindow::on_aff_clicked()
{
    partenaire p;
    QString type=ui->typehistorique->currentText();
    ui->listView->setModel(p.afficher_historique(type));
}

void MainWindow::on_tabpartenaire_activated(const QModelIndex &index)
{

        QString val=ui->tabpartenaire->model()->data(index).toString();
        QSqlQuery qry;
        qry.prepare("SELECT *from partenaire where id='"+val+"' ");
        if (qry.exec())
        {
    while(qry.next())
        {
           ui->idp->setText(qry.value(0).toString());
          ui->nomp->setText(qry.value(1).toString());
            ui->nump->setText(qry.value(2).toString());
             ui->typep->setText(qry.value(3).toString());
             ui->quantitep->setValue(qry.value(4).toInt());
             ui->sommep->setText(qry.value(5).toString());
             ui->date_partenaire->setDate(qry.value(6).toDate());
             ui->idsupp_2->setText(qry.value(0).toString());

        }
        }else
             QMessageBox::question(this, "Interrogatoire", "Erreur", QMessageBox ::Yes );


}

void MainWindow::on_RECHERCHESp_textChanged(const QString &arg1)
{
    partenaire p;
       ui->tabpartenaire->setModel(p.recherchep2(arg1));
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{

    QString val=ui->listView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT *from history where id='"+val+"' ");
    if (qry.exec())
    {
while(qry.next())
    {

      ui->nomsupp->setText(qry.value(2).toString());


    }
    }else
        QMessageBox::question(this, "Interrogatoire", "Erreur", QMessageBox ::Yes );


}

void MainWindow::on_supphistorique_clicked()
{
    QSqlQuery query;

         query.prepare("DELETE from history");

    query.exec();
}

void MainWindow::on_supphistorique_2_clicked()
{
    QMessageBox msgbox;
    int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que vous etes sur de supprimer cet partenaire ?", QMessageBox ::Yes | QMessageBox::No);

partenaire p;
p.setid(ui->nomsupp->text().toInt());

    if (reponse == QMessageBox::Yes)
    {
        bool test=p.supprimerh(p.getid());
        if(test){
            msgbox.setText("suppression avec succes");


        }

    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::information(this, "Careness", "Annulation!");
    }


    msgbox.exec();
}

void MainWindow::on_pdfhistorique_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
            qDebug()<<dir;
            QPdfWriter pdf(dir+"/PdfList.pdf");
                                   QPainter painter(&pdf);
                                  int i = 4000;

                                        painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/Users/ASUS/Desktop/projetcppv5/images/Logo.png"));
                                       // painter.drawText(900,650,"careness");
                                       painter.setPen(Qt::blue);
                                       painter.setFont(QFont("Time New Roman", 25));
                                       painter.drawText(3000,1400,"Liste historique");
                                       painter.setPen(Qt::black);
                                       painter.setFont(QFont("Time New Roman", 15));
                                       painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                       painter.drawRect(100,3000,9400,500);
                                       painter.setFont(QFont("Time New Roman", 9));
                                       painter.drawText(300,3300,"ID");
                                       painter.drawText(2000,3300,"nb_emp");
                                       painter.drawText(4000,3300,"nb_borne");
                                       painter.drawText(5600,3300,"nom_responsable");
                                       painter.drawText(7200,3300,"localisation");

                                       painter.drawRect(100,3000,9400,10700);
                                       //QTextDocument previewDoc;
                                       QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                                       //QTextCursor cursor(&previewDoc);
                                       QSqlQuery query;
                                       query.prepare("select * from history");
                                       query.exec();
                                       while (query.next())
                                       {
                                           painter.drawText(300,i,query.value(0).toString());
                                           painter.drawText(2000,i,query.value(1).toString());
                                           painter.drawText(4000,i,query.value(2).toString());
                                           painter.drawText(5600,i,query.value(3).toString());
                                           painter.drawText(7000,i,query.value(4).toString());
                                           painter.drawText(8000,i,query.value(5).toString());
                                          i = i +500;
                                       }
                                       int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                           QMessageBox::Yes|QMessageBox::No);
                                           if (reponse == QMessageBox::Yes)
                                           {
                                               QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                               painter.end();
                                           }
                                           else
                                           {
                                                painter.end();
                                           }
}

void MainWindow::on_RECHERCHES_2_textChanged(const QString &arg1)
{
   stock s;
       ui->tabstock->setModel(s.recherches2(arg1));
}

void MainWindow::on_tabstock_activated(const QModelIndex &index)
{
    QString val=ui->tabstock->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT *from stock where id='"+val+"' ");
    if (qry.exec())
    {
while(qry.next())
    {
       ui->id->setText(qry.value(0).toString());
      ui->nomStock->setText(qry.value(1).toString());
        ui->typestock->setText(qry.value(3).toString());
         ui->quantite->setText(qry.value(2).toString());
         ui->dates->setDate(qry.value(4).toDate());
         ui->idsupp->setText(qry.value(0).toString());

    }
    }else
         QMessageBox::question(this, "Interrogatoire", "Erreur", QMessageBox ::Yes );
}
void MainWindow::on_pushButton_valid_13_clicked(){


}

void MainWindow::on_btn_retourp_2_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(0);
}

void MainWindow::on_RECHERCHES_textChanged(const QString &arg1)
{
    stock s;
        ui->TABRECHS->setModel(s.recherches2(arg1));
}

void MainWindow::on_stats_clicked()
{
   ui->stackedWidgetbar->setCurrentIndex(5);
    /* partenaire p;
    int  total = p.compteur();
    int totalproduit=p.compteur1();


    QString a=QString("argent"+QString::number(((total*100)/(totalproduit+total)),'f',2)+"%" );
    QString b=QString("produit"+QString::number(((totalproduit*100)/(total+totalproduit)),'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();

                                    series->append("Argent",total);
                                    series->append("produit",totalproduit);
                            if (total!=0)
                            {  QPieSlice *slice = series->slices().at(0);
                                slice->setLabelVisible();
                                slice->setPen(QPen());
                                slice->setLabel(a);}
                            if ( totalproduit!=0)
                            {
                                QPieSlice *slice1 = series->slices().at(1);
                                  slice1->setLabelVisible();
                                  slice1->setLabel(b);
                            }
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend
                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des produits et Argent : nombre total du don: "+ QString::number(totalproduit+total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                    QLabel *label = new QLabel(a,chartView);

                                                                        QFont font("Euphemia");
                                                                           font.setPixelSize(24);
                                                                           label->setFont(font);
                                                                           label->move(50, 50);
                                                                           QLabel *label1 = new QLabel(b,chartView);
                                                                            QLabel *label2 = new QLabel(b,chartView);
                                                                              label1->setFont(font);
                                                                              label1->move(50, 90);
                                                                              QString styleSheet = "background-color: blue; color: white;";
                                                                                 label->setStyleSheet(styleSheet);
                                                                                 QString styleSheet1 = "background-color: black; color: white;";
                                                                                    label1->setStyleSheet(styleSheet1);
                                    chartView->show();*/
}

//information
void MainWindow::on_pushButton_12_clicked()
{

    ui->stackedWidgetbar->setCurrentIndex(1);



}

void MainWindow::on_btn_about_clicked()
{
    sound->play();
    ui->stackedWidgetbar->setCurrentIndex(6);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).


}

void MainWindow::on_stats_3_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(13);
   /* stock p;
    int h = ui->annee_2->text().toInt();
   QString s = ui->annee_2->text();
    int  total = p.compteur(h);
    int totalproduit=p.compteur1();


    QString a=QString("'"+s+"'/"+QString::number(((total*100)/(totalproduit)),'f',2)+"%" );
    QString b=QString("all/"+QString::number((((totalproduit-p.compteur(h))*100)/(totalproduit)),'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();

                                    series->append("s",total);
                                    series->append("all",totalproduit);
                            if (total!=0)
                            {  QPieSlice *slice = series->slices().at(0);
                                slice->setLabelVisible();
                                slice->setPen(QPen());
                                slice->setLabel(a);}
                            if ( totalproduit!=0)
                            {
                                QPieSlice *slice1 = series->slices().at(1);
                                  slice1->setLabelVisible();
                                  slice1->setLabel(b);
                            }
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend

                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des produits et Argent : nombre total du don: "+ QString::number(totalproduit));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                     QLabel *label = new QLabel(a,chartView);

                                     QFont font("Euphemia");
                                        font.setPixelSize(24);
                                        label->setFont(font);
                                        label->move(50, 50);
                                        QLabel *label1 = new QLabel(b,chartView);
                                         QLabel *label2 = new QLabel(b,chartView);
                                           label1->setFont(font);
                                           label1->move(50, 90);
                                           QString styleSheet = "background-color: blue; color: white;";
                                              label->setStyleSheet(styleSheet);
                                              QString styleSheet1 = "background-color: black; color: white;";
                                                 label1->setStyleSheet(styleSheet1);
                                    chartView->show();*/
}

void MainWindow::on_sendmail_clicked()
{
    Smtp * smtp = new Smtp("jihedhorchani@gmail.com" , "pwnpdldwbcokcmcw", "smtp.gmail.com",465);
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            QString msg=ui->msgmail->toPlainText();
     if( !files.isEmpty() )
            smtp->sendMail("jyhed_test",ui->mail->text(),ui->objetmail->text(),msg ,files);
    else
         smtp->sendMail("jyhed_test",ui->mail->text(),ui->objetmail->text(),msg);

             QMessageBox::information(nullptr, QObject::tr("SENT"),
                                      QObject::tr("Email Sended Successfully.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
}
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void MainWindow::addPagination()
{

int currentPage = ui->tabstock->currentIndex().row() / m_pageSize;
int rowCount = ui->tabstock->model()->rowCount();

int startRow = currentPage * m_pageSize;
int endRow = qMin(startRow + m_pageSize, rowCount) - 1;

// Show only the rows for the current page
// QAbstractItemModel *model = ui->tabmedi_3->model();
for (int row = 0; row < rowCount; row++) {
if (row >= startRow && row <= endRow) {
ui->tabstock->setRowHidden(row, false);
} else {
ui->tabstock->setRowHidden(row, true);
}
}
}


void MainWindow::on_moisuivant_clicked()
{
    QModelIndex currentIndex = ui->tabstock->currentIndex();
    int nextIndexRow = currentIndex.row() + m_pageSize;
    int rowCount = ui->tabstock->model()->rowCount();
    if (nextIndexRow >= rowCount) {
    nextIndexRow = rowCount - 1;
    }

    m_currentPage = nextIndexRow / m_pageSize;
    addPagination();

    QModelIndex nextIndex = ui->tabstock->model()->index(nextIndexRow, currentIndex.column());
    ui->tabstock->setCurrentIndex(nextIndex);
}

void MainWindow::on_moisprec_clicked()
{
    m_currentPage--;
    if (m_currentPage < 0) {
    m_currentPage = 0;
    }
    addPagination();

    // Aller à la page précédente
    int prevPageStartRow = m_currentPage * m_pageSize;
    int rowCount = ui->tabstock->model()->rowCount();
    if (prevPageStartRow < rowCount) {
    QModelIndex prevIndex = ui->tabstock->model()->index(prevPageStartRow, 0);
    ui->tabstock->setCurrentIndex(prevIndex);
    }
}

void MainWindow::on_ON_clicked()
{
    notification n;
    A.write_to_arduino("1");
      ui->etat->setText("ON");
      A.ajouteretat("ON");
      n.notification_arduino();
      sound2->play();
      data=A.read_from_arduino();
}

void MainWindow::on_off_clicked()
{
    notification n;
    A.write_to_arduino("0");
     ui->etat->setText("OFF");
     A.ajouteretat("OFF");
     n.notification_arduino1();
     sound3->play();

}
void MainWindow::update_label()
{
    partenaire p;
    notification n;
    data=A.read_from_arduino();
    ui->rfid->setText(data);
   if(data=="3")
{
n.notification_arduino2();
p.ajouter_historique("detection","enfant",0);
Smtp * smtp = new Smtp("jihedhorchani@gmail.com" , "pwnpdldwbcokcmcw", "smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    QString msg=ui->msgmail->toPlainText();

    smtp->sendMail("jyhed_test","jihed.horchani@esprit.tn","Warning","il y a une mouvement ou quelque chose dans le centre");   }

}
//export excel
void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->TABRECHS);

    //colums to export
    obj.addField(0, "entier", "char(20)");
    obj.addField(1, "reel", "char(20)");
    obj.addField(2, "combobox", "char(20)");
    obj.addField(3, "lineedit", "char(20)");
    obj.addField(4, "textedit", "char(20)");
    obj.addField(5, "dateedit", "char(20)");
    obj.addField(5, "timeedit", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void MainWindow::on_exportp_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->listView);

    //colums to export
    obj.addField(0, "entier", "char(20)");
    obj.addField(1, "reel", "char(20)");
    obj.addField(2, "combobox", "char(20)");
    obj.addField(3, "lineedit", "char(20)");
    obj.addField(4, "textedit", "char(20)");
    obj.addField(5, "dateedit", "char(20)");
    obj.addField(5, "timeedit", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}
//site web
void MainWindow::on_pushButton_8_clicked()
{
    QString link="https://www.google.com/?hl=fr";
    QDesktopServices::openUrl(QUrl (link)) ;
}
// gestion event

void MainWindow::on_validevent_clicked()
{
    QMessageBox msgbox;
    int id=ui->idE->text().toInt();
    QString nom=ui->nomE->text();
    QString type=ui->typeE->text();
    int nbrinvit=ui->nbrinvitE->text().toInt();
    QString endroit=ui->endroitE->text();
    QDate Date_event = ui->date_Event->date();
    if (id < 0 || !id)
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme id"),
                    QObject::tr("verifier id\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if (nom.isEmpty())
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter un nom \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if ( type.isEmpty() && endroit.isEmpty() )
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter un type  !! \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if ( endroit.isEmpty() )
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter l'endroit !! \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
  else
    {
     Event E(id,nom,type,nbrinvit,endroit,Date_event);
    E.setid(ui->idE->text().toInt());
    if(E.recherche(E.getid()))
    {
    msgbox.setText("event existe deja");
    }else
    {bool test=E.ajouter();

        if(test){
            msgbox.setText("ajouter avec succes");
        }
   }
        msgbox.exec();
    }
}

void MainWindow::on_pushButton_valid_17_clicked()
{
    Event E;
    ui->tabevent->setModel(E.afficher());
}

void MainWindow::on_supp_event_clicked()
{
    QMessageBox msgbox;
    int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que vous etes sur de supprimer cet event ?", QMessageBox ::Yes | QMessageBox::No);

Event E;
E.setid(ui->idsupp_E->text().toInt());

    if (reponse == QMessageBox::Yes)
    {
        if(E.recherche(E.getid()))
        {
        bool test=E.supprimer(E.getid());
        if(test){
            msgbox.setText("suppression avec succes");
        }
        }else
        msgbox.setText("event introuvable !!");
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::information(this, "Careness", "Annulation!");
    }


    msgbox.exec();
}

void MainWindow::on_pushButton_valid_19_clicked()
{
    Event E;
    QString type=ui->selectri_2->currentText();
    ui->tabevent->setModel(E.tri(type));
}

void MainWindow::on_modifierE_clicked()
{
    QMessageBox msgbox;
    int id=ui->idE->text().toInt();
    QString nom=ui->nomE->text();
    QString type=ui->typeE->text();
    int nbrinvit=ui->nbrinvitE->text().toInt();
    QString endroit=ui->endroitE->text();
    QDate  Date_event = ui->date_Event->date();
    Event E(id,nom,type,nbrinvit,endroit, Date_event);
    E.setid(ui->idE->text().toInt());

   if(E.recherche(E.getid()))
   {
       bool test=E.modifier(id);
   if(test){
       msgbox.setText("modifier avec succes");
   }}else
   msgbox.setText("id introuvable!!");
       msgbox.exec();
}
void MainWindow::on_BRE_clicked()
{
    Event E;
     QString nom=ui->RECHERCHESE->text();
     ui->tabevent->setModel(E.afficherRSE(nom));
}

//fin event



void MainWindow::on_pushButton_13_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
            qDebug()<<dir;
            QPdfWriter pdf(dir+"/PdfList.pdf");
                                   QPainter painter(&pdf);
                                  int i = 4000;

                                        painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/Users/ASUS/Desktop/projetcppv5/images/Logo.png"));
                                       // painter.drawText(900,650,"careness");
                                       painter.setPen(Qt::blue);
                                       painter.setFont(QFont("Time New Roman", 25));
                                       painter.drawText(3000,1400,"Liste des evenements");
                                       painter.setPen(Qt::black);
                                       painter.setFont(QFont("Time New Roman", 15));
                                       painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                       painter.drawRect(100,3000,9400,500);
                                       painter.setFont(QFont("Time New Roman", 9));
                                       painter.drawText(300,3300,"ID");
                                       painter.drawText(2000,3300,"Nom");
                                       painter.drawText(4000,3300,"type");
                                       painter.drawText(5600,3300,"endroit");
                                       painter.drawText(7200,3300,"nombres des invitées");

                                       painter.drawRect(100,3000,9400,10700);
                                       //QTextDocument previewDoc;
                                       QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                                       //QTextCursor cursor(&previewDoc);
                                       QSqlQuery query;
                                       query.prepare("select * from event");
                                       query.exec();
                                       while (query.next())
                                       {
                                           painter.drawText(300,i,query.value(0).toString());
                                           painter.drawText(2000,i,query.value(1).toString());
                                           painter.drawText(4000,i,query.value(2).toString());
                                           painter.drawText(5600,i,query.value(3).toString());
                                           painter.drawText(7000,i,query.value(4).toString());
                                           painter.drawText(8000,i,query.value(5).toString());
                                          i = i +500;
                                       }
                                       int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                           QMessageBox::Yes|QMessageBox::No);
                                           if (reponse == QMessageBox::Yes)
                                           {
                                               QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                               painter.end();
                                           }
                                           else
                                           {
                                                painter.end();
                                           }
}

void MainWindow::on_stats_2_clicked()
{
  ui->stackedWidgetbar->setCurrentIndex(15);
    /* QSqlQueryModel * model= new QSqlQueryModel();
                                        model->setQuery("select * from Event where endroit = 'ariana' ");
                                        float e=model->rowCount();
                                        model->setQuery("select * from Event where endroit = 'stade' ");
                                        float ee=model->rowCount();
                                        model->setQuery("select * from Event where endroit = 'lac' ");
                                        float eee=model->rowCount();
                                        model->setQuery("select * from Event where endroit = 'cst' ");
                                        float eeee=model->rowCount();
                                        float total=e+ee+eee+eeee;
                                        QString a=QString("ariana"+QString::number((e*100)/total,'f',2)+"%" );
                                        QString b=QString("stade"+QString::number((ee*100)/total,'f',2)+"%" );
                                         QString c=QString("lac"+QString::number((eee*100)/total,'f',2)+"%" );
                                          QString d=QString("cst"+QString::number((eeee*100)/total,'f',2)+"%" );
                                        QPieSeries *series = new QPieSeries();
                                        series->append(a,e);
                                        series->append(b,ee);
                                        series->append(c,eee);
                                        series->append(d,eeee);
                                if (e!=0)
                                {QPieSlice *slice = series->slices().at(0);
                                 slice->setLabelVisible();
                                 slice->setPen(QPen());}
                                if ( ee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice1 = series->slices().at(1);
                                         //slice1->setExploded();
                                         slice1->setLabelVisible();
                                }
                                if ( eee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice2 = series->slices().at(2);
                                         //slice1->setExploded();
                                         slice2->setLabelVisible();
                                }
                                if ( eeee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice3 = series->slices().at(3);
                                         //slice1->setExploded();
                                         slice3->setLabelVisible();
                                }
                                        // Create the chart widget
                                        QChart *chart = new QChart();
                                        // Add data to chart with title and hide legend
                                        chart->addSeries(series);
                                        chart->setTitle("Pourcentage des localisations : nombre total : "+ QString::number(total));
                                        chart->legend()->hide();
                                        // Used to display the chart
                                        QChartView *chartView = new QChartView(chart);
                                        chartView->setRenderHint(QPainter::Antialiasing);
                                        chartView->resize(1000,500);
                                        chartView->show();*/
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QDate datee=ui->calendarWidget->selectedDate();
            qDebug() << datee;
            QDate d= datee;
            qDebug() << d;
            QSqlQuery query;
            query.prepare("SELECT id,nom,endroit from event where Date_event = :date");
            query.bindValue(":date",d);
            query.exec();
            QSqlQueryModel * model=new QSqlQueryModel();


                  model->setQuery(query);
                  model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
                  model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                  model->setHeaderData(2, Qt::Horizontal, QObject::tr("endroit"));


                 ui->tableevent->setModel(model);
}

void MainWindow::on_page_event_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(7);
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(8);

}

void MainWindow::on_btn_ogrenci_10_clicked()
{
    sound->play();

        QString TYPE;
        TYPE = ui->GG->text();

                       if (TYPE=="Gestion_event" || TYPE=="Admin") {


       ui->stackedWidgetbar->setCurrentIndex(7);
                       }else {
     QMessageBox::warning(this, "Erreur", "vous n'avez pas l'accés");    }

}

void MainWindow::on_RETOUR1_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(1);

}

void MainWindow::on_ON_2_clicked()
{
     A.write_to_arduino("1"); //envoyer 1 à arduino
     ui->etat_2->setText("ON");
     send_mailtemperature();
     ui->tabarduino_2->setModel(A.afficher_arduino2());
     sound2->play();
}

void MainWindow::on_off_2_clicked()
{
    A.write_to_arduino("2"); //envoyer 1 à arduino
    A.ajouter_temp();
    ui->etat_2->setText("OFF");
    ui->tabarduino_2->setModel(A.afficher_arduino2());

    sound3->play();

}

void MainWindow::on_tabevent_activated(const QModelIndex &index)
{
    QString val=ui->tabevent->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT *from event where id='"+val+"' ");
    if (qry.exec())
    {
while(qry.next())
    {
       ui->idE->setText(qry.value(0).toString());
      ui->nomE->setText(qry.value(1).toString());
        ui->typeE->setText(qry.value(2).toString());
        ui->endroitE->setText(qry.value(3).toString());
         ui->nbrinvitE->setText(qry.value(4).toString());
         ui->date_Event->setDate(qry.value(5).toDate());

         ui->idsupp_E->setText(qry.value(0).toString());

    }
    }else
         QMessageBox::question(this, "Interrogatoire", "Erreur", QMessageBox ::Yes );
}

void MainWindow::on_RECHERCHESE_textChanged(const QString &arg1)
{
    Event E;
       ui->tabevent->setModel(E.recherche2(arg1));
}

void MainWindow::on_browseBtn_clicked()
{
    browse();
}
// mail de temperature
void MainWindow::send_mailtemperature()
{
    data=A.read_from_arduino();

        Smtp * smtp = new Smtp("jihedhorchani@gmail.com" , "pwnpdldwbcokcmcw", "smtp.gmail.com",465);
            connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

            QString msg=ui->msgmail->toPlainText();

            smtp->sendMail("jyhed_test","ines.cherif@esprit.tn","Warning","La temperature a dépassée 30 dégrée Cordialement");


}

void MainWindow::on_darkmode_clicked()
{
    sound->play();

    QApplication::setStyle(QStyleFactory::create("Fusion"));

        QPalette palette;
        palette.setColor(QPalette::Window, QColor(35, 35, 35));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(25, 25, 25));
        palette.setColor(QPalette::AlternateBase, QColor(35, 35, 35));
        palette.setColor(QPalette::ToolTipBase, Qt::black);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(45, 45, 45));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        palette.setColor(QPalette::Link, QColor(42, 130, 218));
        palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        palette.setColor(QPalette::HighlightedText, Qt::black);
        qApp->setPalette(palette);

        qApp->setStyleSheet("QComboBox{border-radius: 10px; border: 1px solid transparent; color: rgb(170, 170, 170);}"
                            "QDateTimeEdit{border-radius: 10px; border: 1px solid transparent; color: rgb(170, 170, 170);}"
                            "QCheckBox{spacing: 5px; outline: none; margin-bottom: 2px; color: rgb(170, 170, 170);}"
                            "QCheckBox::indicator{border-radius: 10px; border: 1px solid #D1D1D1;}"
                            "QSpinBox{color: rgb(170, 170, 170);}"
                            "QPushButton{color: rgb(170, 170, 170); border-radius:10px; background-color: rgb(45, 45, 45); border-width: 2px; font: 75 10pt 'Times New Roman'; border:1px solid rgb(100, 100, 100);}"
                            "QPushButton:hover {border:1px solid rgb(42, 130, 218);}"
                            "QPushButton:pressed {color: rgb(255, 255, 255); background-color: rgb(42, 130, 218);}"
                            "QPushButton:checked{border-color: #6A6969; background-color: rgb(42, 130, 218);}"
                            "QFrame{background-color: rgb(25, 25, 25); border-radius: 10px; border: 1px solid #444; font: 75 10pt 'Times New Roman';}"
                            "QDialog{background-color: rgb(45, 45, 45);}"
                            "QLabel{border: 1px solid transparent; color: rgb(170, 170, 170);}"
                            "QLineEdit{border-radius:10px; border:1px solid; border-color: rgb(100, 100, 100); color: rgb(170, 170, 170);}"
                            "QGroupBox{background-color: rgb(45, 45, 45); border-radius: 10px; border: 1px solid #444; font: 75 10pt 'Times New Roman';}"
                            "ProgressBar:horizontal { border-radius: 6px;  border: 1px solid #3A3939; text-align: center; padding: 1px;background-color:rgb(142, 191, 46);}");
     ui->stackedWidgetbar->setStyleSheet("QStackedWidget{background-image: url(\":/new/prefix1/images/BACKDARK.png\");}");

}

void MainWindow::on_page_event_2_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(1);
}

void MainWindow::on_btn_ogrenci_8_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(9);


}
//gestion enfants
void MainWindow::on_pushButton_valid_22_clicked()
{
    enfants ee;
    ui->tabenfants->setModel(ee.afficher());
}

void MainWindow::on_pushButton_valid_23_clicked()
{
    enfants E;
    QString type=ui->selectri->currentText();
    ui->tabenfants->setModel(E.tri(type));
}

void MainWindow::on_BRE_2_clicked()
{
    enfants E;
     QString nom=ui->RECHERCHESE->text();
     ui->tabenfants->setModel(E.afficherRSp(nom));
}

void MainWindow::on_pushButton_17_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tabenfants->model()->rowCount();
    const int columnCount = ui->tabenfants->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=lightblue link=#5000A0>\n"

        //     "<align='right'> " << datefich << "</align>"
        "<center> <H1>Liste Des evenements </H1></br></br></tr></tr><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tabenfants->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tabenfants->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tabenfants->isColumnHidden(column))
            {
                QString data = ui->tabenfants->model()->data(ui->tabenfants->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
            "</body>\n"
            "<footer>"
            "<div align=right>"
              "Careness"
            "</div>"
            "<div align=left>"
              "Sender Name,signature<br>"
              "Ariana essoughra<br>"
              "Tunis"
            "</div>"
          "</footer>"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}

void MainWindow::on_tabenfants_activated(const QModelIndex &index)
{
    //generer code QR
                QString text ="enfants details :"+ ui->tabenfants->model()->data(ui->tabenfants->model()->index(ui->tabenfants->currentIndex().row(),1)).toString()
                        +" "+ui->tabenfants->model()->data(ui->tabenfants->model()->index(ui->tabenfants->currentIndex().row(),2)).toString()
                        +" "+ui->tabenfants->model()->data(ui->tabenfants->model()->index(ui->tabenfants->currentIndex().row(),3)).toString()
                        +" "+ui->tabenfants->model()->data(ui->tabenfants->model()->index(ui->tabenfants->currentIndex().row(),4)).toString();
                     +" "+ui->tabenfants->model()->data(ui->tabenfants->model()->index(ui->tabenfants->currentIndex().row(),5)).toString();

                using namespace qrcodegen;
                  // Create the QR Code object
                  QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
                  qint32 sz = qr.getSize();
                  QImage im(sz,sz, QImage::Format_RGB32);
                    QRgb black = qRgb(  0,  0,  0);
                    QRgb white = qRgb(255,255,255);
                  for (int y = 0; y < sz; y++)
                    for (int x = 0; x < sz; x++)
                      im.setPixel(x,y,qr.getModule(x, y) ? black : white );
                  ui->QR_code->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );

                  QString val=ui->tabenfants->model()->data(index).toString();
                  QSqlQuery qry;
                  qry.prepare("SELECT *from enfant where id='"+val+"' ");
                  if (qry.exec())
                  {
              while(qry.next())
                  {
                     ui->id2->setText(qry.value(0).toString());
                    ui->nom->setText(qry.value(1).toString());
                      ui->prenom->setText(qry.value(2).toString());
                       ui->age->setText(qry.value(3).toString());
                       ui->date->setDate(qry.value(6).toDate());
                       ui->idsupp_E_2->setText(qry.value(0).toString());

                  }
                  }else
                       QMessageBox::question(this, "Interrogatoire", "Erreur", QMessageBox ::Yes );

}

void MainWindow::on_stat_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(16);
  /*  QSqlQueryModel * model= new QSqlQueryModel();
                                        model->setQuery("select * from enfant where age = '12' ");
                                        float e=model->rowCount();
                                        model->setQuery("select * from enfant where age = '13' ");
                                        float ee=model->rowCount();
                                        model->setQuery("select * from enfant where age = '1' ");
                                        float eee=model->rowCount();
                                        model->setQuery("select * from enfant where age = '10' ");
                                        float eeee=model->rowCount();
                                        float total=e+ee+eee+eeee;
                                        QString a=QString("12   "+QString::number((e*100)/total,'f',2)+"%" );
                                        QString b=QString("13   "+QString::number((ee*100)/total,'f',2)+"%" );
                                         QString c=QString("11  "+QString::number((eee*100)/total,'f',2)+"%" );
                                          QString d=QString("10  "+QString::number((eeee*100)/total,'f',2)+"%" );
                                        QPieSeries *series = new QPieSeries();
                                        series->append(a,e);
                                        series->append(b,ee);
                                        series->append(c,eee);
                                        series->append(d,eeee);
                                if (e!=0)
                                {QPieSlice *slice = series->slices().at(0);
                                 slice->setLabelVisible();
                                 slice->setPen(QPen());}
                                if ( ee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice1 = series->slices().at(1);
                                         //slice1->setExploded();
                                         slice1->setLabelVisible();
                                }
                                if ( eee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice2 = series->slices().at(2);
                                         //slice1->setExploded();
                                         slice2->setLabelVisible();
                                }
                                if ( eeee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice3 = series->slices().at(3);
                                         //slice1->setExploded();
                                         slice3->setLabelVisible();
                                }
                                        // Create the chart widget
                                        QChart *chart = new QChart();
                                        // Add data to chart with title and hide legend
                                        chart->addSeries(series);
                                        chart->setTitle("Pourcentage des localisations : nombre total : "+ QString::number(total));
                                        chart->legend()->hide();
                                        // Used to display the chart
                                        QChartView *chartView = new QChartView(chart);
                                        chartView->setRenderHint(QPainter::Antialiasing);
                                        chartView->resize(1000,500);
                                        chartView->show();*/
}
void MainWindow::sendSMS(QString account_sid, QString auth_token, QString message, QString from_number, QString to_number, QString picture_url, bool verbose)
{
    if (account_sid.isEmpty() || auth_token.isEmpty() || message.isEmpty() || from_number.isEmpty() || to_number.isEmpty()) {
           qDebug() << "You didn't include all necessary inputs!";
           qDebug() << "Call using -h for help.";
           return;
       }

       QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + account_sid + "/Messages.json");
       QNetworkRequest request(url);
       QByteArray auth = QString("%1:%2").arg(account_sid, auth_token).toLocal8Bit().toBase64();
       request.setRawHeader("Authorization", "Basic " + auth);
       request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

       QUrlQuery params;
       params.addQueryItem("From", from_number);
       params.addQueryItem("To", to_number);
       params.addQueryItem("Body", message);
       if (!picture_url.isEmpty()) {
           params.addQueryItem("MediaUrl", picture_url);
       }

       QNetworkAccessManager *manager = new QNetworkAccessManager(this);
       QNetworkReply *reply = manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());

       QObject::connect(reply, &QNetworkReply::finished, [=](){
           QString response = QString(reply->readAll());
           if (reply->error() != QNetworkReply::NoError) {
               qDebug() << "Message send failed.";
               if (verbose && !response.isEmpty()) {
                   qDebug() << "Response:" << response;
               }
           } else {
               if (verbose) {
                   qDebug() << "SMS sent successfully!";
                   qDebug() << "Response:" << response;
               }
           }
           reply->deleteLater();
           manager->deleteLater();
       });

       QObject::connect(manager, &QNetworkAccessManager::authenticationRequired, [&](QNetworkReply *reply, QAuthenticator *authenticator){
           Q_UNUSED(reply);
           authenticator->setUser(account_sid);
           authenticator->setPassword(auth_token);
       });
}

void MainWindow::on_SMS_clicked()
{
    QString account_sid = "ACa33b2ed63a3861e7df731342aebec224";
        QString auth_token = "a843b5727b96ac479a072d244e6d1e70";
        QString from_number = "+16206341138"; // votre numéro Twilio
        QString to_number = "+216 21669169"; // numéro de téléphone du destinataire
        QString message = "Hello, world!"; // message à envoyer
        QString picture_url = ""; // URL de l'image, si vous voulez en envoyer une
        bool verbose = true; // afficher les messages de débogage ou non

        sendSMS(account_sid, auth_token, message, from_number, to_number, picture_url, verbose);
}

void MainWindow::on_supp_enfant_clicked()
{
    QMessageBox msgbox;
    int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que vous etes sur de supprimer cet enfant ?", QMessageBox ::Yes | QMessageBox::No);

enfants E;
E.setid(ui->idsupp_E->text().toInt());

    if (reponse == QMessageBox::Yes)
    {
        if(E.recherche(E.getid()))
        {
        bool test=E.supprimer(E.getid());
        if(test){
            msgbox.setText("suppression avec succes");
        }
        }else
        msgbox.setText("enfant introuvable !!");
    }
    else if (reponse == QMessageBox::No)
    {
        QMessageBox::information(this, "Careness", "Annulation!");
    }


    msgbox.exec();
}

void MainWindow::on_modifierE_2_clicked()
{
    QMessageBox msgbox;
    int id=ui->id->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int age=ui->age->text().toInt();
     QDate date = ui->date->date();
  enfants E(id,nom,prenom,age,date);
    E.setid(ui->id->text().toInt());

   if(E.recherche(E.getid()))
   {
       bool test=E.modifier(id);
   if(test){
       msgbox.setText("modifier avec succes");
   }}else
   msgbox.setText("id introuvable!!");
       msgbox.exec();
}

void MainWindow::on_valide_enfant_clicked()
{

    QMessageBox msgbox;
    int id=ui->id2->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    int age=ui->age->text().toInt();
    QDate date=ui->date->date();
    QRegExp regex1("^[A-Za-z]+$");
    QDateTime Date_convention = ui->date_partenaire->dateTime();
    if (id < 0 || !id)
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme id"),
                    QObject::tr("verifier id\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else if (!regex1.exactMatch(nom))
    {
        QMessageBox::critical(nullptr, QObject::tr("probleme nom"),
                    QObject::tr("Il faut ajouter un nom \n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
  else
    {
    enfants ee(id,nom,prenom,age,date);
    ee.setid(ui->id2->text().toInt());


    if(ee.recherche(ee.getid()))
    {
    msgbox.setText("enfants existe deja");
    }else
    {bool test=ee.ajouter();

        if(test){

            msgbox.setText("ajouter avec succes");


        }
   }
        msgbox.exec();
    }
}

void MainWindow::on_pushButton_19_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(1);
}
//end enfants

void MainWindow::on_defaultmode_clicked()
{
    sound->play();

    QApplication::setStyle(QStyleFactory::create("Fusion"));
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(255,255,255));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(255,255,255));
        palette.setColor(QPalette::AlternateBase, QColor(255,255,255));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(255,255,255));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        palette.setColor(QPalette::Link, QColor(42, 130, 218));
        palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        palette.setColor(QPalette::HighlightedText, Qt::white);
        qApp->setPalette(palette);
        qApp->setStyleSheet("QComboBox{border-radius: 10px; border: 1px solid transparent; color: rgb(25, 139, 186);}"
                            "QDateTimeEdit{border-radius: 10px; border: 1px solid transparent; color: rgb(25, 139, 186);}"
                            "QCheckBox{spacing: 5px; outline: none; margin-bottom: 2px; color: rgb(20, 72, 149);}"
                            "QCheckBox::indicator{border-radius: 10px; border: 1px solid #D1D1D1;}"
                            "QSpinBox{color: rgb(20, 72, 149);}"
                            "QPushButton{color: rgb(25, 139, 186); border-radius:10px; background-color: rgb(255, 255, 255); border-width: 2px; font: 75 10pt 'Times New Roman'; border:1px solid rgb(209, 209, 209);}"
                            "QPushButton:hover {border:1px solid rgb(25, 139, 186);}"
                            "QPushButton:pressed {color: rgb(255, 255, 255); background-color: rgb(20, 175, 218);}"
                            "QPushButton:checked{border-color: #6A6969; background-color: rgb(20, 175, 218);}"
                            "QFrame{background-color: white; border-radius: 10px; border: 1px solid #ccc; font: 75 10pt 'Times New Roman';}"
                            "QDialog{background-color: rgb(25, 139, 186);}"
                            "QLabel{border: 1px solid transparent; color: rgb(20, 72, 149);background-color: rgb(255, 255, 255);}"
                            "QLineEdit{border-radius:10px; border:1px solid; border-color: rgb(209, 209, 209); color: rgb(20, 72, 149);}"
                            "QGroupBox{background-color: white; border-radius: 10px; border: 1px solid #ccc; font: 75 10pt 'Times New Roman';}"
                            "ProgressBar:horizontal { border-radius: 6px;  border: 1px solid #3A3939; text-align: center; padding: 1px;background-color: rgb(209, 209, 209);} "
                            "QProgressBar::chunk:horizontal {border-radius: 6px;background-color: rgb(142, 191, 46);}"
                            "QTableView{background-color: transparent;}");
     ui->stackedWidgetbar->setStyleSheet("QStackedWidget{background-image: url(\":/new/prefix1/images/BQCK.png\");}"
                                         "QTableView{background-color:rgb(255, 255, 255) ;}");

}

void MainWindow::on_btn_ogrenci_7_clicked()
{


    sound->play();

        QString TYPE;
        TYPE = ui->GG->text();

                       if (TYPE=="Gestion_enfant" || TYPE=="Admin") {


       ui->stackedWidgetbar->setCurrentIndex(10);
                       }else {
     QMessageBox::warning(this, "Erreur", "vous n'avez pas l'accés");    }

        }



void MainWindow::on_mode1s_clicked()
{
 sound = new QSound(":/new/prefix1/images/mixkit-game-click-1114.wav", this);
 sound->play();



}

void MainWindow::on_mode2s_clicked()
{

    sound = new QSound(":/new/prefix1/images/soundm2.wav", this);
    sound->play();

}

void MainWindow::on_fullscreenb_clicked()
{
    sound->play();


showFullScreen();








}

void MainWindow::on_normalscreenb_clicked()
{
    sound->play();

     showNormal();


}

void MainWindow::on_btn_minimize_7_clicked()
{
 showMinimized();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString strStream;
            QTextStream out(&strStream);



            const int rowCount = ui->listView->model()->rowCount();
            const int columnCount = ui->listView->model()->columnCount();

            out <<  "<html>\n"
                "<head>\n"

                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                <<  QString("<title>%60 les postes</title>\n").arg("poste")
                <<  "</head>\n"
                "<body bgcolor=#ffffff link=#5000A0>\n"
                "<table border=1 cellspacing=0 cellpadding=2>\n";
            out << "<thead><tr bgcolor=#f0f0f0>";
            for (int column = 0; column < columnCount; column++)
                if (! ui->listView->isColumnHidden(column))
                    out << QString("<th>%1</th>").arg(ui->listView->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->listView->isColumnHidden(column)) {
                        QString data = ui->listView->model()->data(ui->listView->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                    }
                }
                out << "</tr>\n";
            }
            out <<  "</table>\n"
                "</body>\n"
                "</html>\n";

            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);

            QPrinter printer;

            QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
            if (dialog->exec() == QDialog::Accepted) {
                document->print(&printer);
            }

            delete document;
}

void MainWindow::on_pushButton_18_clicked()
{
    QString strStream;
            QTextStream out(&strStream);



            const int rowCount = ui->TABRECHS->model()->rowCount();
            const int columnCount = ui->TABRECHS->model()->columnCount();

            out <<  "<html>\n"
                "<head>\n"

                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                <<  QString("<title>%60 les postes</title>\n").arg("poste")
                <<  "</head>\n"
                "<body bgcolor=#ffffff link=#5000A0>\n"
                "<table border=1 cellspacing=0 cellpadding=2>\n";
            out << "<thead><tr bgcolor=#f0f0f0>";
            for (int column = 0; column < columnCount; column++)
                if (! ui->TABRECHS->isColumnHidden(column))
                    out << QString("<th>%1</th>").arg(ui->TABRECHS->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->TABRECHS->isColumnHidden(column)) {
                        QString data = ui->TABRECHS->model()->data(ui->TABRECHS->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                    }
                }
                out << "</tr>\n";
            }
            out <<  "</table>\n"
                "</body>\n"
                "</html>\n";

            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);

            QPrinter printer;

            QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
            if (dialog->exec() == QDialog::Accepted) {
                document->print(&printer);
            }

            delete document;
}

void MainWindow::on_pushButton_20_clicked()
{
    QTranslator T;
    QStringList langs;
    MainWindow m;
    langs << "English" << "French" <<"Arabic";
    const QString lang= QInputDialog::getItem(NULL,"Language","Select a language :",langs);

    if(lang=="English")
    {
        T.load(":/new/prefix1/images/anglais.qm");
    }else if(lang=="Arabic")
    {
        T.load(":/new/prefix1/images/arabe.qm");
    }

    if(lang!="French")
    {
        qApp->installTranslator(&T);
        QLocale::setDefault(QLocale(lang)); // Définir la locale de l'application sur la langue sélectionnée
    }


    ui->retranslateUi(this);

    qDebug() << "Current language:" << QLocale::system().name();



}

void MainWindow::setCamera(const QCameraInfo &cameraInfo)
{
    Camera = new QCamera(cameraInfo);
    imageCapture = new QCameraImageCapture(Camera);
    Camera->setViewfinder(ui->viewfinder);
    connect(imageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &MainWindow::readyForCapture);
    Camera->stop();

}

void MainWindow::readyForCapture(bool ready)
{
    ui->pushButton_21->setEnabled(ready);
}
void MainWindow::on_pushButton_21_clicked()
{
    notification n;
    isCapturingImage = true;
    imageCapture->capture();
    n.notification_photo();
}

void MainWindow::on_pushButton_23_clicked()
{
    // Stop the camera
   Camera->stop();
    // Reconnect the viewfinder to the camera
    Camera->setViewfinder(ui->viewfinder);
    ui->stackedWidgetbar->update();

}

void MainWindow::on_pushButton_22_clicked()
{
    Camera->start();

}
// gestion employe

void MainWindow::on_pushButton_49_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(1);
}

void MainWindow::on_Continuer_2_clicked()
{
    ui->stackedWidget_11->setCurrentIndex(1);
    QString nomemp=ui->nomemp->text();
    QString prenomemp=ui->prenomemp->text();
}

void MainWindow::on_Annuler_ajout_2_clicked()
{
    ui->stackedWidget_11->setCurrentIndex(0);

}

void MainWindow::on_Ajouter_btn_2_clicked()
{
    QMessageBox msgbox;
    int idemp=ui->IDemp->text().toInt();
     QString nomemp=ui->nomemp->text();
     QString prenomemp=ui->prenomemp->text();



     int cinemp=ui->cinemp->text().toInt();
     QString designationemp=ui->desi_3->currentText();
     QString adresseemp=ui->adresseemp->text();
     QString mdpemp=ui->Mdpemp->text();
     QRegExp Exp_mail ("^[\\w|\\.]+@[\\w]+\\.[\\w]{2,4}$");
     employe emp;
      QRegExp Exp_mdp ("^(?=.*[A-Za-z])(?=.*[0-9])[A-Za-z0-9]{8,}$");
     emp.encrypt(mdpemp);

     bool value=true;

     if (adresseemp.contains(Exp_mail)==false){
         QMessageBox::critical (this, "Validation", " Adresse  n'est pas valide !");
         value=false;
     }

     if (mdpemp.contains(Exp_mdp)==false){
         QMessageBox::critical (this, "Validation", " Mot de passe n'est pas valide ! Doit commencer avec une Majus avec l'exitance d'un chiffre ");
         value=false;

     }

     if (ui->radioButton_4->isChecked()){
         ui->Gender_label_2->setText(ui->radioButton_4->text());
     }else{ ui->Gender_label_2->setText(ui->radioButton_3->text());}
     QString genderemp=ui->Gender_label_2->text();
     int numemp = ui->Telemp->text().toInt();
     employe e(idemp ,nomemp ,prenomemp , genderemp ,cinemp, designationemp , adresseemp , mdpemp , numemp );



if(value==true)
{

     e.setID(ui->IDemp->text().toInt());
     if(e.recherche(e.getID()))
     {
     msgbox.setText("erreur");

    }else
     {
     bool test=e.ajouter();

         if(test){
             msgbox.setText("er avec succes");
         }
    }
        msgbox.exec();
}
}

void MainWindow::on_pushButton_valid_37_clicked()
{
    employe e;
       ui->tableemploye_2->setModel(e.afficher());
}

void MainWindow::on_modifieremp_clicked()
{
    QMessageBox msgbox;

    int id=ui->IDemp->text().toInt();
     QString nom=ui->nomemp->text();
     QString prenom=ui->prenomemp->text();

     QString gender=ui->radioButton_4->text();
     //QString male=ui->radioButton_2->text();
     int cin=ui->cinemp->text().toInt();
     QString adresse=ui->adresseemp->text();
     QString designation=ui->desi_3->currentText();
     QString mdp=ui->Mdpemp->text();

    int num=ui->Telemp->text().toInt();
     employe e(id,nom,prenom , gender ,cin, designation , adresse , mdp , num);

     e.setID(ui->IDemp->text().toInt());

     if(e.recherche(e.getID()))
     {
         bool test=e.modifier(id);
     if(test){
         msgbox.setText("modifier avec succes");
     }}else
     msgbox.setText("id introuvable!!");
         msgbox.exec();
}

void MainWindow::on_tableemploye_2_activated(const QModelIndex &index)
{
    QString val=ui->tableemploye_2->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT *from employe where id='"+val+"' ");
    if (qry.exec())
    {
while(qry.next())
    {
       ui->IDemp->setText(qry.value(0).toString());
      ui->nomemp->setText(qry.value(1).toString());
        ui->prenomemp->setText(qry.value(2).toString());
         ui->cinemp->setText(qry.value(3).toString());
         ui->desi_3->setCurrentText(qry.value(4).toString());
         ui->adresseemp->setText(qry.value(5).toString());
         ui->Mdpemp->setText(qry.value(6).toString());
         ui->Telemp->setText(qry.value(7).toString());
         ui->Gender_label_2->setText(qry.value(8).toString());

         ui->idsupprim_2->setText(qry.value(0).toString());

    }
    }else
         QMessageBox::question(this, "Interrogatoire", "Erreur", QMessageBox ::Yes );

}

void MainWindow::on_supp_partenaire_3_clicked()
{
    QMessageBox msgbox;
employe e1;
e1.setID(ui->idsupprim_2->text().toInt());

bool test=e1.supprimer(e1.getID());

if(test){
    msgbox.setText("suppression avec succes");
}

    msgbox.exec();
}


void MainWindow::on_RECHERCHESp_3_textChanged(const QString &arg1)
{
    employe e;
         ui->tableemploye_2->setModel(e.afficherRSp(arg1));
}

void MainWindow::on_pushButton_48_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
            qDebug()<<dir;
            QPdfWriter pdf(dir+"/PdfList.pdf");
                                   QPainter painter(&pdf);
                                  int i = 4000;

                                        painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/Users/ASUS/Desktop/projetcppv5/images/Logo.png"));
                                       // painter.drawText(900,650,"careness");
                                       painter.setPen(Qt::blue);
                                       painter.setFont(QFont("Time New Roman", 25));
                                       painter.drawText(3000,1400,"Liste des employés");
                                       painter.setPen(Qt::black);
                                       painter.setFont(QFont("Time New Roman", 15));
                                       painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                                       painter.drawRect(100,3000,9400,500);
                                       painter.setFont(QFont("Time New Roman", 9));

                                       painter.drawText(500,3600,"ID");
                                       painter.drawText(2000,3600,"NOM");
                                       painter.drawText(3300,3600,"Prenom");
                                       painter.drawText(4500,3600,"CIN");
                                       painter.drawText(6700,3600,"DESIGNATION");
                                       painter.drawText(8500,3600,"ADRESSE");
                                       painter.setFont(QFont("Times New Roman", 10));
                                       painter.drawRect(100,3300,9400,9000);
                                       //QTextDocument previewDoc;
                                       QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                                       //QTextCursor cursor(&previewDoc);
                                       QSqlQuery query;
                                       query.prepare("select * from employe");
                                       query.exec();
                                       while (query.next())
                                       {
                                           painter.drawText(300,i,query.value(0).toString());
                                           painter.drawText(2000,i,query.value(1).toString());
                                           painter.drawText(4000,i,query.value(2).toString());
                                           painter.drawText(5600,i,query.value(3).toString());
                                           painter.drawText(7000,i,query.value(4).toString());
                                           painter.drawText(8000,i,query.value(5).toString());
                                          i = i +500;
                                       }
                                       int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                           QMessageBox::Yes|QMessageBox::No);
                                           if (reponse == QMessageBox::Yes)
                                           {
                                               QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                               painter.end();
                                           }
                                           else
                                           {
                                                painter.end();
                                           }

}

void MainWindow::on_pushButton_valid_36_clicked()
{
    employe e;
        QString type=ui->selectri_7->currentText();
        ui->tableemploye_2->setModel(e.tri(type));

}

void MainWindow::on_stats_7_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(12);

}

void MainWindow::on_Stat_clicked()
{
  ui->STATISTIQUE->setCurrentIndex(0);

    QSqlQueryModel * model= new QSqlQueryModel();
                                    model->setQuery("select * from employe where gender = 'Homme' ");
                                    float e=model->rowCount();
                                    model->setQuery("select * from employe where gender = 'Femme' ");
                                    float ee=model->rowCount();
                                    float total=e+ee;
                                    QString a=QString("Homme"+QString::number((e*100)/total,'f',2)+"%" );
                                    QString b=QString("Femme"+QString::number((ee*100)/total,'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();
                                    series->append(a,e);
                                    series->append(b,ee);
                            if (e!=0)
                            {QPieSlice *slice = series->slices().at(0);
                             slice->setLabelVisible();
                             slice->setPen(QPen());}
                            if ( ee!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice1 = series->slices().at(1);
                                     //slice1->setExploded();
                                     slice1->setLabelVisible();
                            }
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend
                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des homme et femme : nombre total : "+ QString::number(total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);

                                    QVBoxLayout *layout = new QVBoxLayout(ui->frame);
                                                      layout->addWidget(chartView);
                                                      ui->frame->setLayout(layout);
}

void MainWindow::on_Stat_2_clicked()
{
    ui->STATISTIQUE->setCurrentIndex(1);
    QSqlQueryModel * model= new QSqlQueryModel();
                                    model->setQuery("select * from employe where DESIGNATION = 'Gestion_enfant' ");
                                    float enfant=model->rowCount();
                                    model->setQuery("select * from employe where DESIGNATION = 'Gestion_event' ");
                                    float event=model->rowCount();
                                    model->setQuery("select * from employe where DESIGNATION = 'Gestion_stock' ");
                                    float stock=model->rowCount();
                                    model->setQuery("select * from employe where DESIGNATION = 'Gestion_partenaire' ");
                                    float partenaire=model->rowCount();
                                    float total=enfant+event+stock+partenaire;
                                    QString a=QString("Gestion_enfant"+QString::number((enfant*100)/total,'f',2)+"%" );
                                    QString b=QString("Gestion_event"+QString::number((event*100)/total,'f',2)+"%" );
                                    QString c=QString("Gestion_stock"+QString::number((stock*100)/total,'f',2)+"%" );
                                    QString d=QString("Gestion_partenaire"+QString::number((partenaire*100)/total,'f',2)+"%" );

                                    QPieSeries *series = new QPieSeries();
                                    series->append(a,enfant);
                                    series->append(b,event);
                                    series->append(c,stock);
                                    series->append(d,partenaire);

                            if (enfant!=0)
                            {QPieSlice *slice = series->slices().at(0);
                             slice->setLabelVisible();
                             slice->setPen(QPen());}
                            if ( event!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice1 = series->slices().at(1);
                                     //slice1->setExploded();
                                     slice1->setLabelVisible();
                            }
                            if ( stock!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice1 = series->slices().at(2);
                                     //slice1->setExploded();
                                     slice1->setLabelVisible();
                            } if ( partenaire!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice1 = series->slices().at(3);
                                     //slice1->setExploded();
                                     slice1->setLabelVisible();
                            }
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend
                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des designation : nombre total : "+ QString::number(total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);

                                    QVBoxLayout *layout = new QVBoxLayout(ui->frame_2);
                                                      layout->addWidget(chartView);
                                                      ui->frame_2->setLayout(layout);

                                                      // Create and set the new layout
                                                              QVBoxLayout *layoutt = new QVBoxLayout(ui->frame_2);
                                                              layoutt->addWidget(chartView);
                                                              ui->frame_2->setLayout(layoutt);
}

void MainWindow::on_pushButton_24_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(11);
}

void MainWindow::on_btn_ogrenci_9_clicked()
{
    sound->play();

        QString TYPE;
        TYPE = ui->GG->text();

                       if (TYPE=="Admin") {


       ui->stackedWidgetbar->setCurrentIndex(11);
                       }else {
     QMessageBox::warning(this, "Erreur", "vous n'avez pas l'accés");    }
}

void MainWindow::on_pushButton_25_clicked()
{
    partenaire p;
    int  total = p.compteur();
    int totalproduit=p.compteur1();


    QString a=QString("argent"+QString::number(((total*100)/(totalproduit+total)),'f',2)+"%" );
    QString b=QString("produit"+QString::number(((totalproduit*100)/(total+totalproduit)),'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();

                                    series->append("Argent",total);
                                    series->append("produit",totalproduit);
                            if (total!=0)
                            {  QPieSlice *slice = series->slices().at(0);
                                slice->setLabelVisible();
                                slice->setPen(QPen());
                                slice->setLabel(a);}
                            if ( totalproduit!=0)
                            {
                                QPieSlice *slice1 = series->slices().at(1);
                                  slice1->setLabelVisible();
                                  slice1->setLabel(b);
                            }
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend
                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des produits et Argent : nombre total du don: "+ QString::number(totalproduit+total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                    QLabel *label = new QLabel(a,chartView);

                                                                        QFont font("Euphemia");
                                                                           font.setPixelSize(24);
                                                                           label->setFont(font);
                                                                           label->move(50, 50);
                                                                           QLabel *label1 = new QLabel(b,chartView);
                                                                            QLabel *label2 = new QLabel(b,chartView);
                                                                              label1->setFont(font);
                                                                              label1->move(50, 90);
                                                                              QString styleSheet = "background-color: blue; color: white;";
                                                                                 label->setStyleSheet(styleSheet);
                                                                                 QString styleSheet1 = "background-color: black; color: white;";
                                                                                    label1->setStyleSheet(styleSheet1);

                                                                                    QVBoxLayout *layout = new QVBoxLayout(ui->frame_11);
                                                                                                      layout->addWidget(chartView);
                                                                                                      ui->frame_11->setLayout(layout);
}

void MainWindow::on_pushButton_26_clicked()
{
    int year = ui->annee_2->text().toInt();
            stock p;
            int total = p.compteur(year);
            int totalproduit = p.compteur1();
            QString s = ui->annee_2->text();
            QString a = QString("'"+s+"'/"+QString::number(((total*100)/(totalproduit)),'f',2)+"%");
            QString b = QString("all/"+QString::number((((totalproduit-p.compteur(year))*100)/(totalproduit)),'f',2)+"%");

            QPieSeries *series = new QPieSeries();
            series->append("s", total);
            series->append("all", totalproduit);

            if (total != 0) {
                QPieSlice *slice = series->slices().at(0);
                slice->setLabelVisible();
                slice->setPen(QPen());
                slice->setLabel(a);
            }
            if (totalproduit != 0) {
                QPieSlice *slice1 = series->slices().at(1);
                slice1->setLabelVisible();
                slice1->setLabel(b);
            }

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Pourcentage des produits et Argent : nombre total du don: "+ QString::number(totalproduit));
            chart->legend()->hide();

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);

            QLabel *label = new QLabel(a, chartView);
            QFont font("Euphemia");
            font.setPixelSize(24);
            label->setFont(font);
            label->move(50, 50);

            QLabel *label1 = new QLabel(b, chartView);
            QLabel *label2 = new QLabel(b, chartView);
            label1->setFont(font);
            label1->move(50, 90);

            QString styleSheet = "background-color: blue; color: white;";
            label->setStyleSheet(styleSheet);

            QString styleSheet1 = "background-color: black; color: white;";
            label1->setStyleSheet(styleSheet1);

            QVBoxLayout *layout = new QVBoxLayout(ui->frame_12);
            layout->addWidget(chartView);
            ui->frame_12->setLayout(layout);

            ui->frame_12->repaint();
            QLayout* existingLayout = ui->frame_12->layout();
            if (existingLayout)
            {
                delete existingLayout;
            }

            // Create and set the new layout
            QVBoxLayout *layoutt = new QVBoxLayout(ui->frame_12);
            layoutt->addWidget(chartView);
            ui->frame_12->setLayout(layoutt);


}

void MainWindow::on_pushButton_27_clicked()
{

    ui->stackedWidgetbar->setCurrentIndex(0);
}

void MainWindow::on_deconnection_clicked()
{
    int reponse = QMessageBox::question(this, "Interrogatoire", "Monsieur est ce que tu veux quitter?", QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            QMessageBox::critical(this, "Careness", "A la prochaine !");
            this->hide();
                    Login *l= new Login;
                    l->show();
        }
        else if (reponse == QMessageBox::No)
        {
            QMessageBox::information(this, "Careness", "bienvenue!");
        }

}

void MainWindow::on_btn_ders_5_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(14);
}

void MainWindow::on_pushButton_30_clicked()
{
     ui->stackedWidgetbar->setCurrentIndex(1);
}





void MainWindow::on_pushButton_28_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                        model->setQuery("select * from Event where endroit = 'ariana' ");
                                        float e=model->rowCount();
                                        model->setQuery("select * from Event where endroit = 'stade' ");
                                        float ee=model->rowCount();
                                        model->setQuery("select * from Event where endroit = 'lac' ");
                                        float eee=model->rowCount();
                                        model->setQuery("select * from Event where endroit = 'cst' ");
                                        float eeee=model->rowCount();
                                        float total=e+ee+eee+eeee;
                                        QString a=QString("ariana"+QString::number((e*100)/total,'f',2)+"%" );
                                        QString b=QString("stade"+QString::number((ee*100)/total,'f',2)+"%" );
                                         QString c=QString("lac"+QString::number((eee*100)/total,'f',2)+"%" );
                                          QString d=QString("cst"+QString::number((eeee*100)/total,'f',2)+"%" );
                                        QPieSeries *series = new QPieSeries();
                                        series->append(a,e);
                                        series->append(b,ee);
                                        series->append(c,eee);
                                        series->append(d,eeee);
                                if (e!=0)
                                {QPieSlice *slice = series->slices().at(0);
                                 slice->setLabelVisible();
                                 slice->setPen(QPen());}
                                if ( ee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice1 = series->slices().at(1);
                                         //slice1->setExploded();
                                         slice1->setLabelVisible();
                                }
                                if ( eee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice2 = series->slices().at(2);
                                         //slice1->setExploded();
                                         slice2->setLabelVisible();
                                }
                                if ( eeee!=0)
                                {
                                         // Add label, explode and define brush for 2nd slice
                                         QPieSlice *slice3 = series->slices().at(3);
                                         //slice1->setExploded();
                                         slice3->setLabelVisible();
                                }
                                        // Create the chart widget
                                        QChart *chart = new QChart();
                                        // Add data to chart with title and hide legend
                                        chart->addSeries(series);
                                        chart->setTitle("Pourcentage des localisations : nombre total : "+ QString::number(total));
                                        chart->legend()->hide();
                                        // Used to display the chart
                                        QChartView *chartView = new QChartView(chart);
                                        chartView->setRenderHint(QPainter::Antialiasing);
                                        chartView->resize(1000,500);
                                        QVBoxLayout *layout = new QVBoxLayout(ui->frame_18);
                                                          layout->addWidget(chartView);
                                                          ui->frame_18->setLayout(layout);
}

void MainWindow::on_pushButton_29_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(7);
}

void MainWindow::on_pushButton_31_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM enfant WHERE age < 12");
    float e = model->rowCount();
    model->setQuery("SELECT * FROM enfant WHERE age >= 12");
    float ee = model->rowCount();
    float total = e + ee;
    QString a = QString("Moins de 12 ans: " + QString::number((e * 100) / total, 'f', 2) + "%");
    QString b = QString("Plus de 12 ans: " + QString::number((ee * 100) / total, 'f', 2) + "%");
    QPieSeries *series = new QPieSeries();
    series->append(a, e);
    series->append(b, ee);
    if (e != 0)
    {
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());
    }
    if (ee != 0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage des enfants par âge : nombre total : " + QString::number(total));
    chart->legend()->hide();
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);
    QVBoxLayout *layout = new QVBoxLayout(ui->frame_19);
    layout->addWidget(chartView);
    ui->frame_19->setLayout(layout);
}

void MainWindow::on_pushButton_32_clicked()
{
    ui->stackedWidgetbar->setCurrentIndex(10);
}

void MainWindow::on_off_3_clicked()
{
        QString nom;
        QSqlQuery query;
nom = ui->GG_2->text()+ui->GG_3->text();
        // affichage du nom

        qDebug()<<nom;
        QByteArray name(nom.toUtf8(),16)    ;
        A.write_to_arduino(name);
}

void MainWindow::on_pushButton_valid_24_clicked()
{
    ui->tabarduino_2->setModel(A.afficher_arduino2());
    ui->tabarduino->setModel(A.afficher_arduino());

}

void MainWindow::on_pushButton_33_clicked()
{
    QString link="https://chat.openai.com/";
    QDesktopServices::openUrl(QUrl (link)) ;
}
