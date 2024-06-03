#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include <QStandardItemModel>
#include <QFile>
#include <QFileDialog>
#include <QSound>
#include <QMediaPlayer>
#include <QUrl>
#include "arduino.h"
#include "export.h"
#include<QPropertyAnimation>
#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>

#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <QVideoWidget>
#include <QMediaPlayer>

#include <QPalette>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Arduino A;



    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString * username;
    int m_currentPage = 0;
    const int m_pageSize = 3;
    //QSortFilterProxyModel* proxyModel;
    QStandardItemModel *model;
    QSound *sound = new QSound(":/new/prefix1/images/mixkit-game-click-1114.wav", this);
    QSound *sound1 = new QSound(":/new/prefix1/images/ajoutsound.wav", this);
    QSound *sound2 = new QSound(":/new/prefix1/images/soundactive.wav", this);
    QSound *sound3= new QSound(":/new/prefix1/images/sounddesactive.wav", this);
    QSound *soundm2= new QSound(":/new/prefix1/images/soundm2.wav", this);
public slots:

    QString setUserInfo(const QString& desegnation, const QString& num , const QString& nom, const QString& prenom , const QString& adresse , const QString& cin , const QString& gender);





private slots:
    void on_btn_ogrenci_5_clicked();

    void on_pushButton_clicked();

    void on_btn_ogrenci_6_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_7_clicked();

    void on_validers_clicked();

    void on_supprstock_clicked();

    void on_pushButton_valid_10_clicked();

    void on_pushButton_valid_13_clicked();

    void on_validpartenaire_clicked();

    void on_pushButton_valid_16_clicked();

    void on_supp_partenaire_clicked();

    void on_pushButton_valid_18_clicked();

    void on_selectri_activated(const QString &arg1);

    void on_modifierp_clicked();

    void on_treeStock_clicked();

    void on_modifierStock_clicked();

    void on_pushButton_valid_11_clicked();

    void on_BRS_clicked();

    void on_btn_quitter_clicked();

    void on_btn_gpartenaire_clicked();

    void on_btn_phistorique_clicked();

    void on_btn_retourp_clicked();

    void on_pushButton_valid_14_clicked();

    void on_pushButton_valid_15_clicked();

    void on_BRp_clicked();

    void on_BRS_2_clicked();

    void on_pushButton_6_clicked();

    void on_pdfS_clicked();

    void on_exitb_clicked();

    void on_aff_clicked();

    void on_tabpartenaire_activated(const QModelIndex &index);

    void on_RECHERCHESp_textChanged(const QString &arg1);

    void on_listView_activated(const QModelIndex &index);

    void on_supphistorique_clicked();

    void on_supphistorique_2_clicked();

    void on_pdfhistorique_clicked();

    void on_RECHERCHES_2_textChanged(const QString &arg1);

    void on_tabstock_activated(const QModelIndex &index);

    void on_btn_retourp_2_clicked();

    void on_RECHERCHES_textChanged(const QString &arg1);

    void on_stats_clicked();

    void on_pushButton_12_clicked();

    void on_btn_about_clicked();

    void on_stats_3_clicked();

    void on_sendmail_clicked();

    void on_moisuivant_clicked();

    void on_moisprec_clicked();
     void addPagination();
     void on_ON_clicked();

     void on_off_clicked();
     void update_label();


     void on_pushButton_2_clicked();

     void on_exportp_clicked();

     void on_pushButton_8_clicked();

     void on_validevent_clicked();

     void on_pushButton_valid_17_clicked();

     void on_supp_event_clicked();

     void on_pushButton_valid_19_clicked();

     void on_modifierE_clicked();

     void on_BRE_clicked();

     void on_pushButton_13_clicked();

     void on_stats_2_clicked();

     void on_calendarWidget_clicked(const QDate &date);

     void on_page_event_clicked();

     void on_pushButton_14_clicked();

     void on_btn_ogrenci_10_clicked();

     void on_RETOUR1_clicked();

     void on_ON_2_clicked();

     void on_off_2_clicked();

     void on_tabevent_activated(const QModelIndex &index);

     void on_RECHERCHESE_textChanged(const QString &arg1);
     void browse();


     void on_browseBtn_clicked();
     void send_mailtemperature();
     void showTime();



     void on_darkmode_clicked();

     void on_page_event_2_clicked();

     void on_btn_ogrenci_8_clicked();

     void on_pushButton_valid_22_clicked();

     void on_pushButton_valid_23_clicked();

     void on_BRE_2_clicked();

     void on_pushButton_17_clicked();

     void on_tabenfants_activated(const QModelIndex &index);

     void on_stat_clicked();
     void sendSMS(QString account_sid, QString auth_token, QString message, QString from_number, QString to_number, QString picture_url, bool verbose);


     void on_SMS_clicked();

     void on_supp_enfant_clicked();

     void on_modifierE_2_clicked();

     void on_valide_enfant_clicked();

     void on_pushButton_19_clicked();

     void on_defaultmode_clicked();

     void on_btn_ogrenci_7_clicked();

     void on_mode1s_clicked();

     void on_mode2s_clicked();

     void on_fullscreenb_clicked();

     void on_normalscreenb_clicked();

     void on_btn_minimize_7_clicked();

     void on_pushButton_3_clicked();

     void on_pushButton_18_clicked();

     void on_pushButton_20_clicked();

     void on_pushButton_21_clicked();
     void readyForCapture(bool ready);
     void setCamera(const QCameraInfo &cameraInfo);



     void on_pushButton_23_clicked();

     void on_pushButton_22_clicked();

     void on_pushButton_49_clicked();

     void on_Continuer_2_clicked();

     void on_Annuler_ajout_2_clicked();

     void on_Ajouter_btn_2_clicked();

     void on_pushButton_valid_37_clicked();

     void on_modifieremp_clicked();

     void on_tableemploye_2_activated(const QModelIndex &index);

     void on_supp_partenaire_3_clicked();

     void on_RECHERCHESp_3_textChanged(const QString &arg1);

     void on_pushButton_48_clicked();

     void on_pushButton_valid_36_clicked();

     void on_stats_7_clicked();

     void on_Stat_clicked();

     void on_Stat_2_clicked();

     void on_pushButton_24_clicked();

     void on_btn_ogrenci_9_clicked();

     void on_pushButton_25_clicked();

     void on_pushButton_26_clicked();

     void on_pushButton_27_clicked();

     void on_deconnection_clicked();

     void on_btn_ders_5_clicked();

     void on_pushButton_30_clicked();





     void on_pushButton_28_clicked();

     void on_pushButton_29_clicked();

     void on_pushButton_31_clicked();

     void on_pushButton_32_clicked();

     void on_off_3_clicked();

     void on_pushButton_valid_24_clicked();

     void on_pushButton_33_clicked();

private:
    Ui::MainWindow *ui;

    QByteArray data;
    QStringList files;
     QPropertyAnimation *animation;

     //camera
     QCamera *Camera = nullptr;
     QCameraImageCapture *imageCapture = nullptr;
     QMediaRecorder* mediaRecorder = nullptr;

     QImageEncoderSettings imageSettings;
     QAudioEncoderSettings audioSettings;
     QVideoEncoderSettings videoSettings;
     QString videoContainerFormat;
     bool isCapturingImage = false;
     bool applicationExiting = false;
signals:
    void setCenter(QVariant, QVariant);
    void addMarker(QVariant, QVariant);
};
#endif // MAINWINDOW_H
