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
    MonsterNode* firstMonster;

    Client(string _name, bool _priority, int _orderNumber) {
        name = _name;
        priority = _priority;
        orderNumber = _orderNumber;
        firstMonster = NULL;
        next = NULL;
    }


    void insert(Monster* monster) {
        if (firstMonster == NULL) {
            firstMonster = new MonsterNode(monster);
        } else {
            MonsterNode* temp = new MonsterNode(monster);
            temp->next = firstMonster;
            firstMonster = temp;
        }
    }



    bool checkOrder() { // Checks if all the monsters in the order are reserved
        bool complete = true;
        MonsterNode* temp = firstMonster;
        while (temp != NULL) {
            if (temp->monster->state == 3)
                temp = temp->next;
            else
                complete = false;
        }
        return complete;
    }

    string toString() {
        MonsterNode* temp = firstMonster;
        string order = "";
        while (temp != NULL) {
            order = order + temp->monster->type + ", ";
            temp = temp->next;
        }
        return "Name: " + name + " Order number: " + to_string(orderNumber) + " Priority: " + (priority ? "With priority" : "Without priority") + " Order: " + order;
    }
};

#endif //CLIENT_H
