#include "server_h.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SERVER_H w;
    w.show();

    return a.exec();
}
