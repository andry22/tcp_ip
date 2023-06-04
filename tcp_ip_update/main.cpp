#include "main.h"
#include "mytcpserver.h"


#include <QCoreApplication>

uint16_t  port ;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc < 2 )
        return -1 ;
    try {
        port = atoi (argv[1]) ;
    }
    catch(...) {}  ;
    // сервер приема иотправки сообщений
    MyTcpServer * server = new MyTcpServer() ;
    //  поток, в котором работает сервер ( сокет)
    QThread     * thread = new QThread       ;
    // помещение сервера в поток
    server->moveToThread(thread)  ;
    // слот обработки данных ( переворот данных)
    UpdateData update_data ;

    QObject::connect(server, SIGNAL(signalUpdateReciveData( QByteArray * , bool *)), &update_data ,  SLOT(slotUpdateReciveData(QByteArray *, bool *)) );

    thread->start()  ;


    return a.exec();
}



