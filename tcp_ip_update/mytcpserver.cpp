#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>


extern uint16_t port ;

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    // при появдении нового соединения - открывается сокет соединения
    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, port)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();
    // установка связи при сигналах на прием данных и собственно чтения данных
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{
    while(mTcpSocket->bytesAvailable()>0)
    {
        array += this->mTcpSocket->readAll();
             // отлов конца строки
              if(array.indexOf("\n") >= 0 )
              {
                  // по приходу "\n" данные отправляются в главный поток для переворота
                  isrun = true ;
                  emit signalUpdateReciveData(&array , &isrun)  ;
                  // ожидание завершения обработки данных
                  while(isrun)  ;

                  qDebug() << "SOCKET  update " <<  this->thread()  ;
                  // отправка данных обратно.
                  this->mTcpSocket->write(array);
                  array.clear()  ;
              }
    }
}

void MyTcpServer::slotClientDisconnected()
{
    mTcpSocket->close();
}

UpdateData::UpdateData(QObject *parent) : QObject(parent)
{


}

// слот переворота данных
void UpdateData::slotUpdateReciveData( QByteArray * mass , bool * isrun)
{

    qDebug() << "update "  << this->thread()  ;

    int i = 0 , ai = mass->length() -3 ;
      uint8_t ch ;
      for( ; i<ai ; i++ , ai--)
      {
           ch = (*mass)[ai]   ;

           (*mass) [ai]  = (* mass)[i]   ;
           (*mass) [i]   = ch ;
      }


      *isrun = false ;

}



