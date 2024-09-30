//
// Created by natal on 9/29/2024.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <bits/stdc++.h>
#include "monster.h"
#include "quality.h"

struct Client {
    string name;
    bool priority;
    int orderNumber;
    Client* next;
    Monster* firstMonster;

    Client(string _name, bool _priority, int _orderNumber) {
        name = _name;
        priority = _priority;
        orderNumber = _orderNumber;
        firstMonster = NULL;
        next = NULL;
    }

    void insert(Monster* monster) {
        if (firstMonster == NULL) {
            firstMonster = monster;
        } else {
            Monster* temp = monster;
            temp->next = firstMonster;
            firstMonster = temp;
        }
    }

    bool checkOrder() { // Checks if all the monsters in the order are reserved
        bool complete = true;
        Monster* temp = firstMonster;
        while (temp != NULL) {
            if (temp->state == 1)
                temp = temp->next;
            else
                complete = false;
        }
        return complete;
    }

    string toString() {
        Monster* temp = firstMonster;
        string order = "";
        while (temp != NULL) {
            order = order + temp->name + ", ";
            temp = temp->next;
        }
        return "Name: " + name + " Order number: " + to_string(orderNumber) + " Priority: " + (priority ? "With priority" : "Without priority") + " Order: " + order;
    }
};

#endif //CLIENT_H
