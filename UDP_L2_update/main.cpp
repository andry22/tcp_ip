#include <QCoreApplication>
#include <QThread>
#include "upd_socket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc < 2 )
           return -1 ;

       // сервер приема иотправки сообщений
       UPD_Socket * socket = new UPD_Socket(argv[1],argv[2]) ;
       //  поток, в котором работает сервер ( сокет)
       QThread     * thread = new QThread       ;
       // помещение сервера в поток
       socket->moveToThread(thread)  ;
       // слот обработки данных ( переворот данных)
       UpdateData update_data ;

       QObject::connect(socket, SIGNAL(signalUpdateReciveData( QByteArray * , bool *)), &update_data ,  SLOT(slotUpdateReciveData(QByteArray *, bool *)) );


       thread->start()   ;

    return a.exec();
}
