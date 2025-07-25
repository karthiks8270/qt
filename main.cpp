#include "client_h.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CLIENT_H w;
    w.show();

    return a.exec();
}
