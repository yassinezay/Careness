#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QSystemTrayIcon>
#include <QString>
class notification
{
public:
    notification(){};

void notification_ajout();
void notification_arduino();
void notification_arduino1();
void notification_arduino2();
void notification_photo();


private:
    int num;
};

#endif // NOTIFICATION_H
