#include "Connection2Client.h"
#include "ImageClient.h"
// #include <iostream>
Connection2Client::Connection2Client(QObject *parent) : QObject(parent), m_counter(0) {}

int Connection2Client::counter() const
{
    return m_counter;
}

void Connection2Client::setCounter(int newCounter)
{
    if (m_counter == newCounter)
        return;
    m_counter = newCounter;
    emit counterChanged();
}

void Connection2Client::ejecutar_imagen()
{
    // std::cout << "hola" << std::endl;
    ImageClient client;
    // client.sendImage("127.0.0.1", 12345, "/home/andri/Downloads/paisaje.jpg");
    client.receiveImage("127.0.0.1", 12345, "imagen_recibida.jpg");
}

