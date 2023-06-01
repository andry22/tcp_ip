#include <QCoreApplication>
#include "mytcpserver.h"
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

    MyTcpServer server;

    return a.exec();
}

