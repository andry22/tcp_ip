#include "upd_socket.h"

UPD_Socket::UPD_Socket(QObject *parent)
    : QObject{parent}
{

}

UPD_Socket::UPD_Socket(char * eth_01 , char * eth_02 , QObject *parent)
    : QObject{parent}
{
    socket_in    = new QUdpSocket(this);
    socket_out   = new QUdpSocket(this);


    QHostAddress HA_1 ;
    HA_1.setAddress(QString(eth_01))  ;
    QHostAddress HA_2 ;
    HA_2.setAddress(QString(eth_02))  ;

    // настройка сокета на интерфейс 1
    if(socket_in->bind(HA_1,500))
        qDebug() << HA_1 << " Started"  ;
    else
        qDebug() << HA_1 << " error"  ;
    // настройка сокета на интерфейс 2
    if(socket_out->bind(HA_2,500))
        qDebug() << HA_2 << " Started"  ;
    else
        qDebug() << HA_2 << " error"  ;

}




//************************************************************************************************************

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
