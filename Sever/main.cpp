#include "server.h"
#include "operatedb.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OperateDB::get_instance().connect();
    Server w;
    return a.exec();
}
