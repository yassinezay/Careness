#include "notification.h"


void notification::notification_ajout()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/projetcppv5/images/notification.png"));
    //notifyIcon->setVisible(1);
    notifyIcon->show();
    notifyIcon->showMessage("Careness"," un nouveau partenaire a été ajouter !",QSystemTrayIcon::Information,15000);

}
void notification::notification_arduino()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/projetcppv5/images/notification.png"));
    //notifyIcon->setVisible(1);
    notifyIcon->show();
    notifyIcon->showMessage("Careness"," le capteur est activé !",QSystemTrayIcon::Information,15000);

}
void notification::notification_arduino1()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/projetcppv5/images/notification.png"));
    //notifyIcon->setVisible(1);
    notifyIcon->show();
    notifyIcon->showMessage("Careness"," le capteur est desactivé !",QSystemTrayIcon::Information,15000);

}
void notification::notification_arduino2()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/projetcppv5/images/notification.png"));
    //notifyIcon->setVisible(1);
    notifyIcon->show();
    notifyIcon->showMessage("Careness"," le capteur a détecté un mouvement !",QSystemTrayIcon::Information,15000);

}
void notification::notification_photo()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/ASUS/Desktop/projetcppv5/images/notification.png"));
    //notifyIcon->setVisible(1);
    notifyIcon->show();
    notifyIcon->showMessage("Careness"," le photo a été enregistrer dans votre dossier images!",QSystemTrayIcon::Information,15000);

}
