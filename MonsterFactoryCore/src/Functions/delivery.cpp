#include "../../delivery.h"
#include "../../logFunctions.h"

#include <QDebug>

// Implementación de ClientNode
ClientNode::ClientNode(Client* _client) {
    client = _client;
    next = nullptr;
}

// Implementación de ClientQueue
ClientQueue::ClientQueue() {
    first = nullptr;
    length = 0;
}

bool ClientQueue::isEmpty() {
    return first == nullptr;
}

void ClientQueue::enqueue(Client* client) {
    if (isEmpty()) {
        first = new ClientNode(client);
    } else {
        ClientNode* temp = first;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new ClientNode(client);
    }
    length++;
}

void ClientQueue::enqueueWithMsg(Client* client) {
    enqueue(client);
    writeToDeliveryLog(QString::fromStdString(client->toString()) + " has been received.");
    writeToDeliveryLog("The order: " + QString::fromStdString(client->toString()) + " has been received.");
}

Client* ClientQueue::dequeue() {
    if (isEmpty()) {
        return nullptr;
    } else {
        ClientNode* temp = first;
        first = first->next;
        temp->next = nullptr;
        length--;
        return temp->client;
    }
}

QString ClientQueue::peek() {
    if (isEmpty()) {
        return "";
    }
    return QString::fromStdString(first->client->toString());
}

// Implementación de Delivery
Delivery::Delivery(Storage* _storage, ClientQueue* _normalClientQueue, ClientQueue* _priorityClientQueue) {
    storage = _storage;
    NormalClientQueue = _normalClientQueue;
    PriorityClientQueue = _priorityClientQueue;
}

void Delivery::deliverOrders(Client* client) {
    StrNode* temp = client->firstMonster;
    while (temp != nullptr) {
        temp->state = StrNode::delivered;
        temp = temp->next;
    }
}

bool Delivery::check(QString numOrder, ClientQueue* queue) {
    ClientNode* client = queue->first;
    while (client != nullptr) {
        if (QString::fromStdString(client->client->orderNumber) == numOrder) {

            return false;
        }
        client = client->next;
    }

    return true;
}

void Delivery::deliver(QString numOrder, ClientQueue* queue) {
    ClientNode* client = queue->first;
    while (client != nullptr) {
        if (QString::fromStdString(client->client->orderNumber) == numOrder) {
            client->client->firstMonster->state = StrNode::delivered;
        }
        client = client->next;
    }
}

void Delivery::clearQueue(ClientQueue* queue) {
    Client* current = queue->dequeue();
    while (current != nullptr) {
        delete current;
        current = queue->dequeue();
    }
}

void Delivery::activate() {

    bool first = true;
    Client* firstOnQueuePriority = nullptr;
    Client* client = PriorityClientQueue->dequeue();



    while (client != nullptr) {

        if (client == firstOnQueuePriority) {
            break;
        }

        StrNode* temp = client->firstMonster;
        bool reserved = false;
        bool allReserved = true;

        while (temp != nullptr) {
            MonsterNode* monster = storage->findMonster(temp->name);
            if (monster != nullptr) {
                monster->monster->state = Monster::reserved;
                temp->state = StrNode::reserved;
                reserved = true;
            } else {
                allReserved = false;
            }
            temp = temp->next;
        }

        if (allReserved && check(QString::fromStdString(client->orderNumber), PriorityClientQueue)) {
            writeToDeliveryLog("Order " + QString::fromStdString(client->orderNumber) + " was delivered.");
        } else {
            if (first) {
                firstOnQueuePriority = client;
                first = false;
            }
            if (!reserved) {
                PriorityClientQueue->enqueue(client);
            }
        }

        client = PriorityClientQueue->dequeue();
    }

    bool first2 = true;
    Client* firstOnQueueNormal = nullptr;
    Client* client2 = NormalClientQueue->dequeue();


    while (client2 != nullptr) {

        qDebug() << client2->orderNumber;
        if (client2 == firstOnQueueNormal) {
            break;
        }

        StrNode* temp2 = client2->firstMonster;
        bool reserved = false;
        bool allReserved = true;

        while (temp2 != nullptr) {
            MonsterNode* monster2 = storage->findMonster(temp2->name);
            if (monster2 != nullptr) {
                monster2->monster->state = Monster::reserved;
                temp2->state = StrNode::reserved;
                reserved = true;
            } else {
                allReserved = false;
            }
            temp2 = temp2->next;
        }

        if (allReserved && check(QString::fromStdString(client2->orderNumber), NormalClientQueue)) {
            writeToDeliveryLog("Order " + QString::fromStdString(client2->orderNumber) + " was delivered.");
        } else {
            if (first2) {
                firstOnQueueNormal = client2;
                first2 = false;
            }
            if (!reserved) {
                NormalClientQueue->enqueue(client2);
            }
        }

        client2 = NormalClientQueue->dequeue();
    }
}
