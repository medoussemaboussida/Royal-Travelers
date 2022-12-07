#ifndef ARDUINO_GADOUR_H
#define ARDUINO_GADOUR_H
#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QTextCodec>

class seriallink : public QObject
{
public:
    explicit seriallink(QObject *parent = nullptr);
    ~seriallink();
    void openConnection();
    void closeConnection();
    void write(const char* msg);
    QByteArray read();
    bool isOpen();
    bool isWritable();

private slots:
    void newData();
signals:
    void gotNewData(QByteArray data);
private:
    QSerialPort serial;
QByteArray s;
};

#endif // ARDUINO_GADOUR_H
