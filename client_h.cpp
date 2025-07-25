#include "client_h.h"
#include "ui_client_h.h"

CLIENT_H::CLIENT_H(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CLIENT_H)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);

        // Initialize random seed for qrand()
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Send data immediately and repeat every 5 seconds for demo
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &CLIENT_H::sendData);
        timer->start(5000); // send every 5 seconds

        sendData(); // initial send

}

CLIENT_H::~CLIENT_H()
{
    delete ui;
}
void CLIENT_H::sendData()
{
    const QHostAddress targetAddress("192.168.1.30");
    const quint16 targetPort = 8080;

    const int totalData2 = 30;
    const int subStructsPerPacket = 4;
    const int totalPackets = (totalData2 + subStructsPerPacket - 1) / subStructsPerPacket; // = 8

    for (int i = 0; i < totalPackets; ++i) {
        main_struct packet;
        int remaining = totalData2 - i * subStructsPerPacket;

        int subStructsToFill = qMin(subStructsPerPacket, remaining);
        for (int j = 0; j < subStructsToFill; ++j) {
            int dataIndex = i * subStructsPerPacket + j;
            data_2 &d2 = packet.sub_struct[j];

            d2.ser_no = static_cast<uint8_t>(dataIndex);
            d2.ip_addr = {192, 168, 1, static_cast<uint16_t>(dataIndex + 1)};  // IP ends with 1 to 30

            for (int k = 0; k < 8; ++k) {
                d2.data_values[k] = {1, 2, 3, 4, 5, 6, 7};
            }
        }

        // Clear remaining sub_structs if any (for safety)
        for (int j = subStructsToFill; j < 4; ++j) {
            packet.sub_struct[j] = {};  // zero out
        }

        QByteArray datagram(reinterpret_cast<const char*>(&packet), sizeof(main_struct));
        socket->writeDatagram(datagram, targetAddress, targetPort);
        qDebug() << "Sent packet" << i + 1 << "of size" << datagram.size();
    }
}

