#ifndef UPD_SOCKET_H
#define UPD_SOCKET_H

#include <QObject>
#include <qDebug>
#include <QHostAddress>
#include <QString>
#include <QNetworkInterface>
#include <QUdpSocket>

class UPD_Socket : public QObject
{
    Q_OBJECT
public:
    explicit UPD_Socket(QObject *parent = nullptr);
    explicit UPD_Socket(char * eth_01 , char * eth_02  , QObject *parent = nullptr);

   QUdpSocket * socket_in  ;
   QUdpSocket * socket_out  ;
signals:
   void slotUpdateReciveData( QByteArray * mass , bool * isrun)  ;
};

class UpdateData : public QObject
{
    Q_OBJECT
public:
    explicit UpdateData(QObject *parent = 0);

public slots:
    // переворот принимаемых данных
    void slotUpdateReciveData( QByteArray * mass , bool * isrun)  ;

};



#endif // UPD_SOCKET_H
