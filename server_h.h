#ifndef SERVER_H_H
#define SERVER_H_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QMap>
#include <QObject>


#pragma pack(push, 1)
typedef struct {
    uint16_t a;
    uint16_t b;
    uint16_t c;
    uint16_t d;
    uint16_t e;
    uint16_t f;
    uint16_t g;
} my_data;

typedef struct {
    uint16_t ip_digit_1;
    uint16_t ip_digit_2;
    uint16_t ip_digit_3;
    uint16_t ip_digit_4;
} ip;

typedef struct {
    uint8_t ser_no;
    ip ip_addr;
    my_data data_values[8];
} data_2;

typedef struct {
    data_2 sub_struct[4];
} main_struct;
#pragma pack(pop)
namespace Ui {
class SERVER_H;
}

class SERVER_H : public QMainWindow
{
    Q_OBJECT

public:
    explicit SERVER_H(QWidget *parent = 0);
    ~SERVER_H();

private slots:
    void onDataReceived();
private:
    Ui::SERVER_H *ui;
    QUdpSocket* socket;
        QString basePath;
        QMap<int, QPair<QDateTime, QString>> folderFileMap;
        QString getFilePathForFolder(int folderIndex);
};

#endif // SERVER_H_H
