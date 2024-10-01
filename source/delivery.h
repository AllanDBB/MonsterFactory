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

void writeToOrderLog(const string& mensaje) {
    ofstream bitacora;

    bitacora.open("C:/Users/natal/Desktop/u/2024/segundo semestre/estructuras de datos/bitacoraPedidos.txt", ios::app);

    if (bitacora.is_open()) {
        bitacora << mensaje << endl;
        bitacora.close();
    } else {
        cout << "No se pudo abrir el archivo de bitácora." << endl;
    }
}

struct Delivery {
    Storage* storage;
    Client* firstNormalClient;
    Client* firstPriorityClient;

    Delivery(Storage* _storage) {
        firstNormalClient = NULL;
        firstPriorityClient = NULL;
        storage = _storage;
    }

    void insertNormal(Client* client) {
        if (firstNormalClient == NULL) {
            firstNormalClient = client;
        } else {
            client->next = firstNormalClient;
            firstNormalClient = client;
        }
        writeToOrderLog("[" + getTimestamp() + "] " + client->toString());
        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client->toString() + " has been received.");
    }

    void insertPriority(Client* client) {
        if (firstPriorityClient == NULL) {
            firstPriorityClient = client;
        } else {
            client->next = firstPriorityClient;
            firstPriorityClient = client;
        }
        writeToOrderLog("[" + getTimestamp() + "] " + client->toString());
        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client->toString() + " has been received.");
    }


    void insert(Client* client) {
        if (client->priority == true) {
            insertPriority(client);
        } else {
            insertNormal(client);
        }
    }

    void deliverOrders(Client* client) {
        MonsterNode* temp = client->firstMonster;
        while (temp != NULL) {
            temp->monster->state = Monster::delivered;
            temp = temp->next;
        }
    }

    void activate() { //ERROR: NO FUNCIONA PARA PEDIDOS CON MÁS DE UN MONSTRUO
        Client * client = firstPriorityClient;

        while (client != NULL) {
            MonsterNode* temp = client->firstMonster;

            while (temp != NULL) {
                cout<<temp->monster->type;
                MonsterNode* foundMonster = storage->findMonster(temp->monster->type);

                if (foundMonster != nullptr && foundMonster->monster->state == Monster::inStock) {
                    foundMonster->monster->state = Monster::reserved;
                    temp->monster->state = Monster::reserved;

                    if (client->checkOrder() == true) {
                        deliverOrders(client);
                        writeToOrderLog("[" + getTimestamp() + "] The order: " + client->toString() + " has been delivered.");
                        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client->toString() + " has been delivered.");
                    }
                }

                temp = temp->next;
            }
            client = client->next;
        }

        Client * client2 = firstNormalClient;

        while (client2 != NULL) {
            MonsterNode* temp2 = client2->firstMonster;

            while (temp2 != NULL) {
                MonsterNode* foundMonster2 = storage->findMonster(temp2->monster->type);

                if (foundMonster2 != nullptr && foundMonster2->monster->state == Monster::inStock) {
                    foundMonster2->monster->state = Monster::reserved;
                    temp2->monster->state = Monster::reserved;

                    if (client2->checkOrder() == true) {
                        deliverOrders(client2);
                        writeToOrderLog("[" + getTimestamp() + "] The order: " + client2->toString() + " has been delivered.");
                        writeToGeneralLog("[" + getTimestamp() + "] The order: " + client2->toString() + " has been delivered.");
                    }
                }

                temp2 = temp2->next;
            }
            client2 = client2->next;
        }
    }

};

#endif //DELIVERY_H
