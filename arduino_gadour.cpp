#include "arduino_gadour.h"

seriallink::seriallink(QObject *parent) : QObject{parent}
{
    s = " ";

    serial.setPortName("COM7");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    connect(&serial, &QSerialPort::readyRead, this, &seriallink::read);
}

seriallink::~seriallink(){
    closeConnection();
}

void seriallink::openConnection(){
    if(!serial.open(QIODevice::ReadWrite)){
        serial.setDataTerminalReady(true);
        qDebug() << "Connexion impossible.";
    } else {
        qDebug() << "Connexion etablie.";
    }
}

void seriallink::write(const char* msg){
    serial.write(msg);
}

bool seriallink::isOpen(){
    return serial.isOpen();
}

bool seriallink::isWritable(){
    return serial.isWritable();
}

void seriallink::closeConnection(){
    serial.close();
}

void seriallink::newData(){
    serial.readAll();
}

QByteArray seriallink::read(){
if(serial.isReadable()){
     s = serial.readAll();
    return s;}
}
