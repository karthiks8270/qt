#include "server_h.h"
#include "ui_server_h.h"

SERVER_H::SERVER_H(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SERVER_H)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    basePath = "C:/Users/GH/Music/data_qt";
    if(!socket->bind(QHostAddress("192.168.1.30"), 8080))
    {
        qDebug()<<"Socket Failed";
    }
    connect(socket,QUdpSocket::readyRead, this, SERVER_H::onDataReceived);
}

SERVER_H::~SERVER_H()
{
    delete ui;
}
QString SERVER_H::getFilePathForFolder(int folderIndex) {
    QDateTime currentTime = QDateTime::currentDateTime();

    if (!folderFileMap.contains(folderIndex) ||
        folderFileMap[folderIndex].first.msecsTo(currentTime) > 30 * 60 * 1000) {

        QString dateStr = QDate::currentDate().toString("yyyy-MM-dd");
        QString timeStr = currentTime.toString("HH-mm-ss");
        QString folderPath = QString("%1/Folder%2/%3").arg(basePath).arg(folderIndex).arg(dateStr);

        QDir dir;
        dir.mkpath(folderPath);

        QString newFilePath = folderPath + "/" + timeStr + ".txt";
        folderFileMap[folderIndex] = qMakePair(currentTime, newFilePath);
    }

    return folderFileMap[folderIndex].second;
}

void SERVER_H::onDataReceived() {
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());

        qDebug() << "Received datagram of size:" << datagram.size();

        if (datagram.size() < sizeof(main_struct)) {
            qWarning() << "Invalid datagram size. Skipping...";
            continue;
        }

        int totalStructs = datagram.size() / sizeof(main_struct);
        const main_struct* structs = reinterpret_cast<const main_struct*>(datagram.constData());

        for (int i = 0; i < totalStructs; ++i) {
            const main_struct& mStruct = structs[i];

            for (int j = 0; j < 30; ++j) {
                const data_2& entry = mStruct.sub_struct[j];

                int folderIndex = entry.ip_addr.ip_digit_4; // last digit of IP
                if (folderIndex < 1 || folderIndex > 30) {
                    qWarning() << "Invalid folder index:" << folderIndex;
                    continue;
                }

                QString filePath = getFilePathForFolder(folderIndex);
                qDebug() << "Writing to file:" << filePath;

                QFile file(filePath);
                if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                    qWarning() << "Failed to open file:" << filePath;
                    continue;
                }

                QTextStream out(&file);
                out << "Serial No: " << entry.ser_no << "\n";
                out << "IP: "
                    << entry.ip_addr.ip_digit_1 << "."
                    << entry.ip_addr.ip_digit_2 << "."
                    << entry.ip_addr.ip_digit_3 << "."
                    << entry.ip_addr.ip_digit_4 << "\n";

                for (int k = 0; k < 8; ++k) {
                    const my_data& d = entry.data_values[k];
                    out<<"Current_Time:"<<QTime::currentTime().toString("HH:mm:ss");
                    out << QString("Data[%1]: a=%2 b=%3 c=%4 d=%5 e=%6 f=%7 g=%8\n")
                           .arg(k).arg(d.a).arg(d.b).arg(d.c).arg(d.d).arg(d.e).arg(d.f).arg(d.g);
                }

                out << "----------------------------\n";
                file.flush();  // Ensures data is flushed immediately
                file.close();
            }
        }
    }
}
