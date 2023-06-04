#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    QByteArray array ;

    bool isrun = true ;

public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotClientDisconnected();
signals :
    void signalUpdateReciveData( QByteArray * , bool *) ;
private:
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
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


#endif // MYTCPSERVER_H
