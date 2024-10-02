//
// Created by natal on 9/29/2024.
//

#include "cliente.h"
#include <bits/stdc++.h>
#include "monster.h"
#include "quality.h"
#include "storage.h"

#ifndef DELIVERY_H
#define DELIVERY_H

struct ClientNode {

    Client* client;
    ClientNode* next;

    ClientNode(Client* _client) {
        client = _client;
        next = nullptr;
    };

};

struct ClientQueue {
    ClientNode* first;


    ClientQueue() {
        first = nullptr;

    }

    bool isEmpty() {
        if (first == nullptr)
            return true;
        else
            return false;
    }

    void enqueue(Client* client) {
        if (isEmpty())
            first = new ClientNode(client);

        else {
            ClientNode* temp = first;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            ClientNode* newClient = new ClientNode(client);
            temp->next = newClient;
        }

        writeToOrderLog("[" + getTimestamp() + "] " + client->toString() + " has been received.");
        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client->toString() + " has been received.");
    }

    Client* dequeue() {
        if (isEmpty())
            return nullptr;
        else {
            ClientNode* temp = first;
            first = first->next;
            temp->next = nullptr;
            return temp->client;
        }

    }

    string peek() {
        if (isEmpty())
            return "";

        return first->client->toString();
    }
};

struct Delivery {
    Storage* storage;
    //Client* firstNormalClient;
    //Client* firstPriorityClient;
    ClientQueue* NormalClientQueue;
    ClientQueue* PriorityClientQueue;

    Delivery(Storage* _storage, ClientQueue* _normalClientQueue, ClientQueue* _priorityClientQueue) {
        //firstNormalClient = nullptr;
        //firstPriorityClient = nullptr;
        storage = _storage;
        NormalClientQueue = _normalClientQueue;
        PriorityClientQueue = _priorityClientQueue;
    }

    void deliverOrders(Client* client) {
        StrNode* temp = client->firstMonster;
        while (temp != nullptr) {
            temp->state = StrNode::delivered;
            temp = temp->next;
        }

    }

    bool check(string numOrder, ClientQueue * queue) {
        ClientNode * client = queue->first;
        while (client != nullptr) {
            if (client->client->orderNumber == numOrder) {
                if (client->client->firstMonster->state == StrNode::reserved) {
                    client = client -> next;
                } else {
                    return false;
                }
            }

        }
        return true;
    }

    void deliver(string numOrder, ClientQueue * queue) {
        ClientNode * client = queue->first;
        while (client != nullptr) {
            if (client->client->orderNumber == numOrder) {
                client->client->firstMonster->state == StrNode::delivered;
            }
        }
    }

    //Pasa lo siguiente: en el activate se supone que para cada cliente que tenemos busca en cada monstruo que pidió (que vienen de tipo StrNode) si se encuentra
    //missing, si es así´, entonces podemos usar la función findMonster(str del nombre del monstruo a buscar) que nos devuelve un puntero a un monstruo disponible
    //o un nullptr si no hay; entonces en caso de que si nos dé un puntero deberíamos de cambiar el estaod del monstruo del almacen y del monstruo del pedido a reserved
    //seguidamente usamos checkOrder(cliente) para ver si todos los monstruos que pidió están reservados, en caso de estarlo se entregan con deliverOrders(client) que los
    //marca como entregados y luego se anade a la biotacora.
    //Así para cada monstruo del pedido para cada cliente de la cola prioritaria y de la cola normal
    //Hay que trabajarlo con colas de prioridad porque lo dice la instrucción y por eso tenemos las dos, en esta implementación intenté usar el len asociado a las inserts del
    //client, y hacer una función aparte para segmentarlo, solo para ver si debía o no volver a encolar.
    //es un asunto con esto de la cola porque hay que hacerle dequeue entonces por eos hice que retornara bool, entonces pudiera saber que si da true es porque se entregó
    //el pedido y no hay que reanadirlo a la cola, si sale false entonces debe volver pero para evitar el loop hice así a lo chancho una cola temporal donde iba metiendo las cosas que
    //dieron false, cuando acaba con los elementos de la cola, esta se reinicia con los valores de la cola temporal y la otra le pongo el first en null seg[un yo para que se vacíe
    //mis problemas son: 1. las colas de prioridad
    //2. los segundos o m[as monstruos en esta implementacion:
    /*
    *ClientNode* client= PriorityClientQueue->first;

        while (client->client != nullptr) {

            StrNode* temp = client->client->firstMonster;

            while (temp != nullptr) {
                cout<<temp->name;
                MonsterNode* foundMonster = storage->findMonster(temp->name);

                if (foundMonster != nullptr) {
                    foundMonster->monster->state = Monster::reserved;
                    temp->state = StrNode::reserved;


                    if (client->client->checkOrder() == true) {
                        deliverOrders(client->client);
                        writeToOrderLog("[" + getTimestamp() + "] The order: " + client->client->toString() + " has been delivered.");
                        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client->client->toString() + " has been delivered.");
                    }
                }

                temp = temp->next;
            }
            client = client->next;
        }

        ClientNode * client2 = NormalClientQueue->first;

        while (client2 != nullptr) {
            StrNode* temp2 = client2->client->firstMonster;

            while (temp2 != nullptr) {
                MonsterNode* foundMonster2 = storage->findMonster(temp2->name);

                if (foundMonster2 != nullptr) {
                    foundMonster2->monster->state = Monster::reserved;
                    temp2->state = StrNode::reserved;

                    if (client2->client->checkOrder() == true) {
                        deliverOrders(client2->client);
                        writeToOrderLog("[" + getTimestamp() + "] The order: " + client2->client->toString() + " has been delivered.");
                        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client2->client->toString() + " has been delivered.");
                    }
                }

                temp2 = temp2->next;
            }
            client2 = client2->next;
        }
    }
     */
    // esa evidentemente no las trabaja como colas, traté de hacerla con colas pero volvía a los mismos errores de siempre.
    // la versi[on de justo aca abajo es una mierda pero por si acaso ahi esta, no hace nada


    /*
    bool activateClient(Client * client) {
        StrNode* temp = client->firstMonster;
        int count = client->len;

        while (count != 0) {
            if (temp->state == StrNode::missing) {
                MonsterNode * monster = storage->findMonster(temp->name);
                if (monster != nullptr) {
                    temp->state = StrNode::reserved;
                    monster->monster->state=Monster::reserved;

                    if (client->checkOrder()) {
                        deliverOrders(client);
                        writeToOrderLog("[" + getTimestamp() + "] The order: " + client->toString() + " has been delivered.");
                        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client->toString() + " has been delivered.");
                        return false;
                    }
                }
            }

            temp = temp->next;
            count--;
        }
        return true;
    }

    void activate() {
        ClientQueue * again = new ClientQueue();
        Client * client = PriorityClientQueue->dequeue();
        while (client != nullptr) {
            if (activateClient(client)) {
                again->enqueue(client);
            }
            client = PriorityClientQueue->dequeue();
        }

        PriorityClientQueue=again;
        again->first = nullptr;

        ClientQueue * again2 = new ClientQueue();
        Client * client2 = NormalClientQueue->dequeue();
        while (client2 != nullptr) {
            if (activateClient(client2)) {
                again->enqueue(client2);
            }
            client2 = NormalClientQueue->dequeue();
        }

        NormalClientQueue=again2;
        again2->first = nullptr;
    }*/


    //esta versión se encicla eternamente, ese es mi mayor problema
    void activate() {
        ClientQueue * again = new ClientQueue();
        Client * client = PriorityClientQueue->dequeue();
        while (client != nullptr) {
            StrNode* temp = client->firstMonster;
            while (temp != nullptr) {
                MonsterNode * foundMonster = storage->findMonster(temp->name);
                if (foundMonster != nullptr) {
                    foundMonster->monster->state = Monster::reserved;
                    temp->state = StrNode::reserved;


                    if (client->checkOrder() == true) {
                        deliverOrders(client);
                        writeToDelivery("[" + getTimestamp() + "] The order: " + client->toString() + " has been delivered.");
                        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client->toString() + " has been delivered.");
                    } else {
                        again->enqueue(client);
                    }
                }
                temp = temp->next;
            }
            client = PriorityClientQueue->dequeue();
        }

        PriorityClientQueue = again;
        again->first = nullptr;



        ClientQueue * again2 = new ClientQueue();
        Client * client2 = NormalClientQueue->dequeue();
        while (client2 != nullptr) {
            StrNode* temp2 = client2->firstMonster;
            while (temp2 != nullptr) {
                MonsterNode * foundMonster = storage->findMonster(temp2->name);
                if (foundMonster != nullptr) {
                    foundMonster->monster->state = Monster::reserved;
                    temp2->state = StrNode::reserved;


                    if (client2->checkOrder() == true) {
                        deliverOrders(client2);
                        writeToDelivery("[" + getTimestamp() + "] The order: " + client2->toString() + " has been delivered.");
                        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client2->toString() + " has been delivered.");
                    } else {
                        again2->enqueue(client2);
                    }
                }
                temp2 = temp2->next;
            }
            client2 = NormalClientQueue->dequeue();
        }

        NormalClientQueue = again;
        again2->first = nullptr;
    }
};

#endif //DELIVERY_H
