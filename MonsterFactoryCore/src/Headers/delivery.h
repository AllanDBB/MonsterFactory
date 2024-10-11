#ifndef DELIVERY_H
#define DELIVERY_H

#include "cliente.h"
#include "monster.h"
#include "quality.h"
#include "storage.h"
#include <QString>
#include <QDebug>

struct ClientNode {
    Client* client;
    ClientNode* next;

    ClientNode(Client* _client);
};

struct ClientQueue {
    ClientNode* first;
    int length;
    ClientQueue();

    bool isEmpty();
    void enqueue(Client* client);
    void enqueueWithMsg(Client* client);
    Client* dequeue();
    QString peek();
};

struct Delivery {
    Storage* storage;
    ClientQueue* NormalClientQueue;
    ClientQueue* PriorityClientQueue;

    Delivery(Storage* _storage, ClientQueue* _normalClientQueue, ClientQueue* _priorityClientQueue);

    void deliverOrders(Client* client);
    bool check(QString numOrder, ClientQueue* queue);
    void deliver(QString numOrder, ClientQueue* queue);
    void clearQueue(ClientQueue* queue);
    void activate();
};

#endif // DELIVERY_H
