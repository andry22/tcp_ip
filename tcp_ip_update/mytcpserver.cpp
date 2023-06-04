#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>


extern uint16_t port ;
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

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
                  isrun = true ;
                  emit signalUpdateReciveData(&array , &isrun)  ;

                  while(isrun)  ;

                  qDebug() << "SOCKET  update " <<  this->thread()  ;

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



