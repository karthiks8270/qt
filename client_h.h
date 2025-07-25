#ifndef CLIENT_H_H
#define CLIENT_H_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QtGlobal>
#include <cstdlib>
#include <ctime>
#include <struct.h>
#include <QMainWindow>


namespace Ui {
    class CLIENT_H;
}
class CLIENT_H : public QMainWindow {
    Q_OBJECT
public:
    explicit CLIENT_H(QWidget *parent = 0);
    ~CLIENT_H();

private slots:
    void sendData();

private:
    Ui::CLIENT_H *ui;
    QUdpSocket *socket;

};


#endif // CLIENT_H_H
