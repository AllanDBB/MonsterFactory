//
// Created by natal on 9/29/2024.
//

#include "client.h"
#include <bits/stdc++.h>
#include "monster.h"
#include "quality.h"
#include "storage.h"

#ifndef DELIVERY_H
#define DELIVERY_H

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
            writeToOrderLog("["+getTimestamp()+"] " +firstNormalClient->toString());
            writeToGeneralLog("["+getTimestamp()+"] The order: " +firstNormalClient->toString()+ " has been received.");
        } else {
            Client* temp = client;
            writeToOrderLog("["+getTimestamp()+"] " +temp->toString());
            writeToGeneralLog("["+getTimestamp()+"] The order: " +temp->toString()+ " has been received.");
            temp->next = firstNormalClient;
            firstNormalClient = temp;
        }
    }

    void insertPriority(Client* client) {
        if (firstPriorityClient == NULL) {
            firstPriorityClient = client;
            writeToOrderLog("["+getTimestamp()+"] " +firstPriorityClient->toString());
            writeToGeneralLog("["+getTimestamp()+"] The order: " +firstPriorityClient->toString()+ " has been received.");
        } else {
            Client* temp = client;
            writeToOrderLog("["+getTimestamp()+"] " +temp->toString());
            writeToGeneralLog("["+getTimestamp()+"] The order: " +temp->toString()+ " has been received.");
            temp->next = firstPriorityClient;
            firstPriorityClient = temp;
        }
    }

    void insert(Client* client) {
        if (client->priority == true) {
            insertPriority(client);
        } else {
            insertNormal(client);
        }
    }

    void deliverOrders(Client* client) {
        Monster* temp = client->firstMonster;
        while (temp != NULL) {
            temp->state = 2; // mark all monsters as delivered
            temp = temp->next;
        }
    }

    void activate() {
        Client* temp = firstPriorityClient;
        while (temp != NULL) {
            Monster* monster = temp->firstMonster;
            while (monster != NULL) {
                Monster* reviewing = storage->first;
                while (reviewing != NULL) {
                    if (reviewing->state == 0 && reviewing->name == monster->name) {
                        reviewing->state = 1; // mark as reserved
                        monster->state = 1;

                        if (temp->checkOrder() == true) {
                            deliverOrders(temp);
                            writeToOrderLog("["+getTimestamp()+"] The order: "+temp->toString()+" has been delivered.");
                            writeToGeneralLog("["+getTimestamp()+"] The order: "+temp->toString()+" has been delivered.");
                        }
                    }
                    reviewing = reviewing->next;
                }
                monster = monster->next;
            }
            temp = temp->next;
        }

        Client* temp2 = firstNormalClient;
        while (temp2 != NULL) {
            Monster* monster = temp2->firstMonster;
            while (monster != NULL) {
                Monster* reviewing = storage->first;
                while (reviewing != NULL) {
                    if (reviewing->state == 0 && reviewing->name == monster->name) {
                        reviewing->state = 1; // mark as reserved
                        monster->state = 1;

                        if (temp2->checkOrder() == true) {
                            deliverOrders(temp2);
                            writeToOrderLog("["+getTimestamp()+"] The order: "+temp2->toString()+" has been delivered.");
                            writeToGeneralLog("["+getTimestamp()+"] The order: "+temp2->toString()+" has been delivered.");
                        }
                    }
                    reviewing = reviewing->next;
                }
                monster = monster->next;
            }
            temp2 = temp2->next;
        }
    }

    /*void print() {
        Client* temp = firstClient;
        while (temp != NULL) {
            temp->print();
            temp=temp->next;
        }
    }*/
};

#endif //DELIVERY_H
